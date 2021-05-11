#pragma once

#include <string>

#include <stem/Buffer.hpp>

namespace stem {

class Geometry {
public:
  Geometry();
  ~Geometry();
  void setIndex(const IndexBuffer buffer);
  void setAttribute(const std::string name, const FloatBuffer buffer);
};

} // namespace stem