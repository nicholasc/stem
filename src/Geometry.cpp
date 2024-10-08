#include <algorithm>

#include <stem/Error.hpp>
#include <stem/Geometry.hpp>

namespace stem {

Geometry::Geometry(const std::vector<Attribute> attributes) {
  // iterate and set attributes
  for (Attribute attribute : attributes) {
    setAttribute(attribute);
  }
}

void Geometry::setIndex(const IndexBuffer index) {
  _index = index;
}

void Geometry::setAttribute(const Attribute attribute) {
  // store the attribute
  _attributes.try_emplace(attribute.name, attribute);

  // generate update draw range count lambda
  const auto updateRangeCount = [this, attribute](auto &&buffer) -> void {
    _range.count = std::max(_range.count, (uint16_t)(buffer.getSize() / attribute.size));
  };

  // visit buffer & update draw range count
  std::visit(updateRangeCount, attribute.buffer);
}

void Geometry::setRange(const Range range) {
  _range = range;
}

void Geometry::setRange(const uint16_t start, const uint16_t count) {
  _range = {start, count};
}

void Geometry::draw(Program program) {
  // create vertex array object if never drew program before
  if (_ids.find(program.getId()) == _ids.end()) {
    createVAO(program); 
  }

  // draw arrays without index
  if (!_index) {
    glAssert(glDrawArrays(GL_TRIANGLES, _range.start, _range.count));
  } else {
    // retrieve & bind the index buffer
    IndexBuffer &index = _index.value();
    index.bind();

    // draw our geometry elements
    glAssert(
      glDrawElements(GL_TRIANGLES, index.getSize(), index.getType(), nullptr)
    );
  }
}

void Geometry::destroy() {
  // iterate and destroy buffer attributes
  for (auto attribute : _attributes) {
    std::visit(
      [](auto &&buffer) { buffer.destroy(); },
      static_cast<BufferVariant>(attribute.second.buffer)
    );
  }

  // iterate and destroy vertex arrays
  for (uint32_t i = 0; i < _ids.size(); i++) {
    glAssert(glDeleteVertexArrays(1, &_ids[i]));
  }
}

void Geometry::createVAO(Program program) {
  // generate empty id at program location
  _ids.insert({program.getId(), 0});
  uint32_t *id = &_ids[program.getId()];

  // create & bind the vertex array
  glAssert(glGenVertexArrays(1, id));
  glAssert(glBindVertexArray(*id));

  // iterate program' active attributes
  for (const auto pair : program.getAttributes()) {
    const std::string name = pair.first;
    const uint32_t location = pair.second.location;

    // attempt to find a corresponding geometry attribute
    const auto iterator = _attributes.find(name);
    if (iterator == _attributes.end()) continue;

    // retrieve the geometry attribute size & buffer
    const Attribute &attribute = iterator->second;
    const BufferVariant &buffer = iterator->second.buffer;

    // generate a bind attribute lamba
    const auto bindAttribute = [location, attribute](auto &&buffer) -> void {
      buffer.bind();

      // vertex attribute to our currently bound buffer
      glAssert(glEnableVertexAttribArray(location));
      glAssert(glVertexAttribPointer(
        location,
        attribute.size,
        buffer.getType(),
        attribute.normalized,
        attribute.stride,
        (void *)attribute.offset
      ));
    };

    // visit buffer & bind it to attribute
    std::visit(bindAttribute, buffer);
  }
}

} // namespace stem