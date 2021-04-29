#pragma once

#include <string>
#include <glad/gl.h>
#include <stem/Exception.hpp>

namespace stem {

class ShaderSyntaxError : public Exception {
public:
  /// @brief ShaderSyntaxError's class constructor
  /// @param id The faulty shader's OpenGL identifier
  /// @return ShaderSyntaxError
  ShaderSyntaxError(const uint32_t id);
};

template <uint32_t type>
class Shader {
private:
  /// @brief The shader's OpenGL identifier
  uint32_t _id = 0;

public:
  /// @brief Shader's constructor
  /// @return Shader
  Shader();

  /// @brief Shader's constructor
  /// @param source A string containing the shader's source code
  /// @return Shader
  Shader(const std::string source);

  /// @brief Shader's deconstructor
  /// @return void
  ~Shader();

  /// @brief Compiles the shader source code
  /// @return void
  void compile() const;

  /// @brief Destroys the shader instance
  /// @return void
  void destroy();

  /// @brief Returns the shader identifier
  /// @return The shader identifier
  const uint32_t getId() const;

  /// @brief Sets the shader source
  /// @param source A string containing the shader's source code
  /// @return void
  void setSource(const std::string &source) const;
};

#include "Shader.inl"

typedef Shader<GL_COMPUTE_SHADER> ComputeShader;
typedef Shader<GL_VERTEX_SHADER> VertexShader;
typedef Shader<GL_TESS_CONTROL_SHADER> TessControlShader;
typedef Shader<GL_TESS_EVALUATION_SHADER> TessEvaluationShader;
typedef Shader<GL_GEOMETRY_SHADER> GeometryShader;
typedef Shader<GL_FRAGMENT_SHADER> FragmentShader;

} // namespace stem