#pragma once

#include <glad/gl.h>

namespace stem {

template <uint32_t BufferType, typename ValueType>
class Buffer {
public:
  /// @brief Defines possible buffer usage methods
  enum Usage {
    Stream = GL_STREAM_DRAW,
    Dynamic = GL_DYNAMIC_DRAW,
    Static = GL_STATIC_DRAW
  };

  /// @brief Buffer constructor
  /// @param array The buffer's data array
  /// @return Buffer
  Buffer(const std::vector<ValueType> array);

  /// @brief Buffer constructor
  /// @param array The buffer's data array
  /// @param usage The buffer's data usage method
  /// @return Buffer
  Buffer(const std::vector<ValueType> array, const Usage usage);

  /// @brief Buffer destructor
  /// @return void
  ~Buffer();

  /// @brief Destroys the buffer instance
  /// @return voi
  void destroy();

  /// @brief Binds the buffer for usage
  /// @return void
  void bind() const;

private:
  /// @brief The internal gl buffer identifier
  uint32_t _id;
};

#include "Buffer.inl"

// declare basic buffer types
typedef Buffer<GL_ARRAY_BUFFER, float> FloatBuffer;
typedef Buffer<GL_ARRAY_BUFFER, uint32_t> Uint32Buffer;
typedef Buffer<GL_ARRAY_BUFFER, uint16_t> Uint16Buffer;
typedef Buffer<GL_ARRAY_BUFFER, uint8_t> Uint8Buffer;
typedef Buffer<GL_ARRAY_BUFFER, int32_t> Int32Buffer;
typedef Buffer<GL_ARRAY_BUFFER, int16_t> Int16Buffer;
typedef Buffer<GL_ARRAY_BUFFER, int8_t> Int8Buffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER, uint32_t> IndexBuffer;

} // namespace stem