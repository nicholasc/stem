template <uint32_t BufferType, typename ValueType>
Buffer<BufferType, ValueType>::Buffer(const std::vector<ValueType> array) :
  Buffer(array, Stream){};

template <uint32_t BufferType, typename ValueType>
Buffer<BufferType, ValueType>::Buffer(
  const std::vector<ValueType> array,
  const Usage usage
) {
  glGenBuffers(1, &_id);
  bind();

  glBufferData(BufferType, array.size() * sizeof(ValueType), &array[0], usage);
}

template <uint32_t BufferType, typename ValueType>
Buffer<BufferType, ValueType>::~Buffer() {
  destroy();
}

template <uint32_t BufferType, typename ValueType>
void Buffer<BufferType, ValueType>::destroy() {
  glDeleteBuffers(1, &_id);
  _id = 0;
}

template <uint32_t BufferType, typename ValueType>
void Buffer<BufferType, ValueType>::bind() const {
  glBindBuffer(BufferType, _id);
}