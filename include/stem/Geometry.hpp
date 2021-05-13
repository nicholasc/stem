#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <stem/Buffer.hpp>
#include <stem/Program.hpp>

namespace stem {

class Geometry {
public:
  /// @brief Defines a simple geometry attribute
  struct Attribute {
    /// @brief The attribute' name
    std::string name;

    /// @brief A single attribute' size in the buffer
    int32_t size = 1;

    /// @brief The attribute' consecutive byte offset
    int32_t stride = 0;

    /// @brief Whether fixed-point data values should be normalized
    bool normalized = false;

    /// @brief The first attribute' offset
    signed long int offset = 0;

    /// @brief The attribute' buffer variant
    BufferVariant buffer;
  };

  /// @brief Geometry constructor
  /// @return Geometry
  Geometry(const std::vector<Attribute> attributes);

  /// @brief Sets the index buffer attribute for the geometry
  /// @param buffer The index buffer to assign to the geometry
  /// @return void
  void setIndex(const IndexBuffer buffer);

  /// @brief Sets a specific buffer attribute for the geometry
  /// @param attribute The attribute to set
  /// @return void
  void setAttribute(const Attribute attribute);

  /// @brief Draws the geometry to the current context using a program
  /// @param program The program to use to draw the geometry
  /// @return void
  void draw(Program program);

  /// @brief Destroys the vertex array instances
  /// @return void
  void destroy();

private:
  /// @brief The internal gl vertex array identifiers for a specific program
  std::unordered_map<uint32_t, uint32_t> _ids;

  /// @brief The geometry' buffer attributes
  std::unordered_map<std::string, Attribute> _attributes;
};

} // namespace stem