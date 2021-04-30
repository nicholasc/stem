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

class ProgramLinkException : public Exception {
public:
  /// @brief ProgramLinkException's class constructor
  /// @param id The faulty program's OpenGL identifier
  /// @return ProgramLinkException
  ProgramLinkException(const uint32_t id);
};

class Program {
private:
  /// @brief The internal gl program identifier
  uint32_t _id;

  /// @brief Compiles, attaches and destroys a shader to the program.
  /// @param type The type of shader we're compiling
  /// @param source The shader's source code
  /// @return void
  void compile(const GLenum type, const std::string &source) const;

public:
  /// @brief Allowed settings when creating a program
  struct Settings {
    const std::string vertex;
    const std::string fragment;
    const std::string geometry;
  };

  /// @brief Program constructor
  /// @param settings The program settings
  /// @return Program
  Program(const Settings settings);

  /// @brief Program destructor
  /// @return void
  ~Program();

  /// @brief Returns the shader identifier
  /// @return The shader identifier
  const uint32_t getId() const;

  /// @brief Binds the program for usage in the current rendering state
  /// @return void
  void use() const;

  /// @brief Destroys the program instance
  /// @return void
  void destroy();
};

} // namespace stem