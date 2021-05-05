#pragma once

#include <string>
#include <variant>
#include <utility>
#include <vector>
#include <unordered_map>

#include <glad/gl.h>
#include <stem/Exception.hpp>
#include <stem/math/Vector.hpp>

namespace stem {

class ShaderSyntaxError : public Exception {
public:
  /// @brief ShaderSyntaxError' class constructor
  /// @param id The faulty shader' OpenGL identifier
  /// @return ShaderSyntaxError
  ShaderSyntaxError(const uint32_t id);
};

class ProgramLinkException : public Exception {
public:
  /// @brief ProgramLinkException' class constructor
  /// @param id The faulty program' OpenGL identifier
  /// @return ProgramLinkException
  ProgramLinkException(const uint32_t id);
};

class Program {
public:
  /// @brief Defines posible variations for uniform values
  typedef std::variant<
    int,
    unsigned int,
    float,
    double,
    Vector2i,
    Vector2u,
    Vector2f,
    Vector2d>
    UniformValue;

  /// @brief A simple uniform structure
  struct Uniform {
    /// @brief The uniform' name
    std::string name;

    /// @brief The uniform' value
    UniformValue value;
  };

  /// @brief Allowed settings when creating a program
  struct Settings {
    /// @brief The vertex shader source
    const std::string vertex;

    /// @brief The fragment shader source
    const std::string fragment;

    /// @brief The geometry shader source
    const std::string geometry;

    /// @brief The uniforms data
    const std::vector<Uniform> uniforms;
  };

  /// @brief Program constructor
  /// @param settings The program settings
  /// @return Program
  Program(const Settings settings = Settings());

  /// @brief Program destructor
  /// @return void
  ~Program();

  /// @brief Returns the shader identifier
  /// @return The shader identifier
  const uint32_t getId() const;

  /// @brief Sets the value of an active uniform if it exists
  /// @param name The name of the targeted active uniform
  /// @param value The value to set
  /// @return void
  void setUniform(const std::string name, const UniformValue value);

  /// @brief Sets the value of an active uniform if it exists
  /// @param uniform The uniform data for the targeted active uniform
  /// @return void
  void setUniform(const Uniform uniform);

  /// @brief Binds the program for usage
  /// @return void
  void use();

  /// @brief Destroys the program instance
  /// @return void
  void destroy();

private:
  /// @brief Stores the state of an active uniform
  struct ActiveUniform {
    /// @brief The active uniform' location
    const int location;

    /// @brief The active uniform' type
    const uint32_t type;

    /// @brief The active uniform' latest value
    UniformValue value;

    /// @brief Whether the active uniform' value needs to be updated on the gpu
    bool needsUpdate = false;

    /// @brief ActiveUniform constructor
    /// @param location The active uniform' location
    /// @param type The active uniform' type
    /// @return ActiveUniform
    ActiveUniform(const int location, const uint32_t type) :
      location(location), type(type) {
    }
  };

  /// @brief Compiles, attaches and destroys a shader to the program.
  /// @param type The type of shader we're compiling
  /// @param source The shader's source code
  /// @return void
  inline void compile(const GLenum type, const std::string &source) const;

  /// @brief The internal gl program identifier
  uint32_t _id;

  /// @brief The program' active uniforms
  std::unordered_map<std::string, ActiveUniform> _activeUniforms;
};

} // namespace stem