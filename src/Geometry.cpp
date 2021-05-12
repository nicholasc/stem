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

Geometry::~Geometry() {
  // iterate and destroy buffer attributes
  for (Attribute attribute : _attributes) {
    std::visit(
      [](auto &&buffer) { buffer.destroy(); },
      static_cast<BufferAttribute>(attribute.second)
    );
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

    // iterate & assign attributes to the program
    for (Attribute attribute : _attributes) {
      const std::string name = attribute.first;

      // find the attribute index in the program if it exists
      const int index = glGetAttribLocation(program.getId(), name.c_str());
      if (index == -1) continue;

      // visit the buffer attribute
      std::visit(
        [index](auto &&buffer) {
          buffer.bind();

          // point vertex attribute to our currently bound buffer
          glEnableVertexAttribArray(index);
          glVertexAttribPointer(
            index, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)0
          );
        },
        attribute.second
      );
    }
  }
}

} // namespace stem