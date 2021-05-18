template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
Buffer<GLBufferType, GLValueType, ValueType>::Buffer(
  const std::vector<ValueType> array
) :
  Buffer(array, Stream){};

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
Buffer<GLBufferType, GLValueType, ValueType>::Buffer(
  const std::vector<ValueType> array,
  const Usage usage
) {
  glGenBuffers(1, &_id);
  bind();

  _size = array.size() * sizeof(ValueType);

  glBufferData(GLBufferType, _size, &array[0], usage);
}

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
void Buffer<GLBufferType, GLValueType, ValueType>::destroy() {
  glDeleteBuffers(1, &_id);
  _id = 0;
}

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
void Buffer<GLBufferType, GLValueType, ValueType>::bind() const {
  glBindBuffer(GLBufferType, _id);
}

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
const uint32_t Buffer<GLBufferType, GLValueType, ValueType>::getId() const {
  return _id;
}

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
const uint32_t Buffer<GLBufferType, GLValueType, ValueType>::getSize() const {
  return _size;
}

template <uint32_t GLBufferType, uint32_t GLValueType, typename ValueType>
const uint32_t Buffer<GLBufferType, GLValueType, ValueType>::getType() const {
  return _type;
}