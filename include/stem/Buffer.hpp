#pragma once

#include <variant>
#include <glad/gl.h>

namespace stem {

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
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

  /// @brief Destroys the buffer instance
  /// @return voi
  void destroy();

  /// @brief Binds the buffer for usage
  /// @return void
  void bind() const;

  /// @brief Returns the current buffer id
  /// @return The current buffer id
  const uint32_t getId() const;

  /// @brief Returns the current buffer size
  /// @return The current buffer size
  const uint32_t getSize() const;

  /// @brief Returns the current buffer type
  /// @return The current buffer type
  const uint32_t getType() const;

private:
  /// @brief The buffer' gl identifier
  uint32_t _id;

  /// @brief The buffer size
  uint32_t _size;

  /// @brief The buffer' gl type
  uint32_t _type = GLValueType;
};

#include "Buffer.inl"

// declare default buffer types
typedef Buffer<GL_ARRAY_BUFFER, GL_FLOAT, float> FloatBuffer;
typedef Buffer<GL_ARRAY_BUFFER, GL_UNSIGNED_INT, uint32_t> Uint32Buffer;
typedef Buffer<GL_ARRAY_BUFFER, GL_UNSIGNED_INT, uint16_t> Uint16Buffer;
typedef Buffer<GL_ARRAY_BUFFER, GL_UNSIGNED_INT, uint8_t> Uint8Buffer;
typedef Buffer<GL_ARRAY_BUFFER, GL_INT, int32_t> Int32Buffer;
typedef Buffer<GL_ARRAY_BUFFER, GL_INT, int16_t> Int16Buffer;
typedef Buffer<GL_ARRAY_BUFFER, GL_INT, int8_t> Int8Buffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_INT, uint32_t> IndexBuffer;

// define posible buffer variations
typedef std::variant<
  FloatBuffer,
  Uint32Buffer,
  Uint16Buffer,
  Uint8Buffer,
  Int32Buffer,
  Int16Buffer,
  Int8Buffer,
  IndexBuffer>
  BufferVariant;

} // namespace stem