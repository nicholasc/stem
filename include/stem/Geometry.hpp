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

  /// @brief The geometry draw range start & count without index buffer
  struct Range {
    /// @brief The draw range start index
    uint16_t start = 0;

    /// @brief The draw range count
    uint16_t count = 0;
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

  /// @brief Sets the geometry draw range
  /// @param range The draw range to apply to this geometry
  /// @return void
  void setRange(const Range range);

  /// @brief Sets the geometry draw range
  /// @param start The draw range start index
  /// @param count The draw range count
  /// @return void
  void setRange(const uint16_t start, const uint16_t count);

  /// @brief Draws the geometry to the current context using a program
  /// @param program The program to use to draw the geometry
  /// @return void
  void draw(Program program);

  /// @brief Destroys the vertex array instances
  /// @return void
  void destroy();

private:
  /// @brief The internal gl vertex array identifiers for specific programs
  std::unordered_map<uint32_t, uint32_t> _ids;

  /// @brief The geometry' index buffer instance
  std::optional<IndexBuffer> _index;

  /// @brief The geometry' buffer attributes
  std::unordered_map<std::string, Attribute> _attributes;

  /// @brief The geometry' internal draw range reference
  Range _range;

  /// @brief Creates a vertex array object for a specific program id
  void createVAO(Program program);
};

} // namespace stem