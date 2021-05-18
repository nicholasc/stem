#pragma once

#include <cstdint>

namespace stem {

#ifdef STEM_DEBUG

  /// Declare OpenGL statement assertion macro
  /// Do while for if/else usage
  #define glAssert(statement)                                                  \
    do {                                                                       \
      statement;                                                               \
      glCheckError(__FILE__, __LINE__, #statement);                            \
    } while (0)

#else

  /// Empty macro for release
  #define glAssert(statement) (statement);

#endif

/// @brief Checks whether OpenGL generated an error on the last statement
/// @param file The absolute filepath of the erroneous source file
/// @param line The line number where the error occured
/// @param expression A string representation of the faulty line
/// @return void
void glCheckError(
  const char *file,
  const uint32_t line,
  const char *expression
);

} // namespace stem