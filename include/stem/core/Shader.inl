template <uint32_t type>
Shader<type>::Shader() {
  _id = glCreateShader(type);
}

template <uint32_t type>
Shader<type>::Shader(const std::string source) {
  _id = glCreateShader(type);
  setSource(source);
}

template <uint32_t type>
Shader<type>::~Shader() {
  destroy();
}

template <uint32_t type>
void Shader<type>::compile() const {
  glCompileShader(_id);

  GLint success;
  glGetShaderiv(_id, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    throw ShaderSyntaxError(_id);
  }
}

template <uint32_t type>
void Shader<type>::destroy() {
  glDeleteShader(_id);
  _id = 0;
}

template <uint32_t type>
const uint32_t Shader<type>::getId() const {
  return _id;
}

template <uint32_t type>
void Shader<type>::setSource(const std::string &source) const {
  const char *src = source.c_str();
  glShaderSource(_id, 1, &src, 0);
}