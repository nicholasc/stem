#include <stem/Geometry.hpp>

namespace stem {

Geometry::Geometry(const std::vector<Attribute> attributes) {
  // iterate and set attributes
  for (Attribute attribute : attributes) {
    const std::string name = attribute.first;
    const BufferAttribute buffer = attribute.second;

    setAttribute(name, buffer);
  }
}

void Geometry::setAttribute(
  const std::string name,
  const BufferAttribute buffer
) {
  // store the attribute
  _attributes.try_emplace(name, buffer);
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
    for (auto pair : program.getAttributes()) {
      const std::string &name = pair.first;
      const Program::ActiveAttribute &attribute = pair.second;

      // attempt to find a corresponding geometry attribute
      auto iterator = _attributes.find(name);
      if (iterator == _attributes.end()) continue;

      // generate a bind attribute lamba
      const auto bindAttribute = [attribute](auto &&buffer) {
        buffer.bind();

        // vertex attribute to our currently bound buffer
        glEnableVertexAttribArray(attribute.location);
        glVertexAttribPointer(
          attribute.location,
          2, // size based on active attribute gl type
          buffer.getType(),
          GL_FALSE,
          sizeof(float) * 2, // stride base on attribute type
          (void *)0          // offset should be based on the attribute
        );
      };

      // visit the buffer attribute & bind it
      std::visit(bindAttribute, iterator->second);
    }
  }

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Geometry::destroy() {
  // iterate and destroy buffer attributes
  for (Attribute attribute : _attributes) {
    std::visit(
      [](auto &&buffer) { buffer.destroy(); },
      static_cast<BufferAttribute>(attribute.second)
    );
  }

  // iterate and destroy vertex arrays
  for (size_t i = 0; i < _ids.size(); i++) {
    glDeleteVertexArrays(1, &_ids[i]);
  }
}

} // namespace stem