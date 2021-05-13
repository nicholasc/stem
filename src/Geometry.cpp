#include <stem/Geometry.hpp>

namespace stem {

Geometry::Geometry(const std::vector<Attribute> attributes) {
  // iterate and set attributes
  for (Attribute attribute : attributes) {
    setAttribute(attribute);
  }
}

void Geometry::setAttribute(const Attribute attribute) {
  // store the attribute
  _attributes.try_emplace(attribute.name, attribute);
}

void Geometry::draw(Program program) {
  // create vertex array object if never drew program before
  if (_ids.find(program.getId()) == _ids.end()) {
    // generate empty id at program location
    _ids.insert({program.getId(), 0});
    uint32_t *id = &_ids[program.getId()];

    // create & bind the vertex array
    glGenVertexArrays(1, id);
    glBindVertexArray(*id);

    // iterate program' active attributes
    for (const auto pair : program.getAttributes()) {
      const std::string name = pair.first;
      const uint32_t location = pair.second.location;

      // attempt to find a corresponding geometry attribute
      const auto iterator = _attributes.find(name);
      if (iterator == _attributes.end()) continue;

      // retrieve the geometry attribute size & buffer
      const int32_t size = iterator->second.size;
      const BufferVariant &buffer = iterator->second.buffer;

      // generate a bind attribute lamba
      const auto bindAttribute = [location, size](auto &&buffer) -> void {
        buffer.bind();

        // vertex attribute to our currently bound buffer
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(
          location,
          size,
          buffer.getType(),
          GL_FALSE,          // normalized or not
          sizeof(float) * 2, // stride base on attribute type
          (void *)0          // offset should be based on the attribute
        );
      };

      // visit the buffer attribute & bind it
      std::visit(bindAttribute, buffer);
    }
  }

  glDrawArrays(GL_TRIANGLES, 0, 6);
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
  for (size_t i = 0; i < _ids.size(); i++) {
    glDeleteVertexArrays(1, &_ids[i]);
  }
}

} // namespace stem