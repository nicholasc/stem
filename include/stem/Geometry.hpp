#pragma once

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>

#include <stem/Buffer.hpp>
#include <stem/Program.hpp>

namespace stem {

class Geometry {
public:
  /// @brief Defines posible variations for attribute values
  typedef std::variant<
    FloatBuffer,
    Uint32Buffer,
    Uint16Buffer,
    Uint8Buffer,
    Int32Buffer,
    Int16Buffer,
    Int8Buffer>
    BufferAttribute;

  /// @brief Defines a simple geometry attribute
  typedef std::pair<const std::string, const BufferAttribute> Attribute;

  /// @brief Geometry constructor
  /// @return Geometry
  Geometry(const std::vector<Attribute> attributes);

  /// @brief Geometry destructor
  /// @return void
  ~Geometry();

  /// @brief Sets the index buffer attribute for the geometry
  /// @param buffer The index buffer to assign to the geometry
  /// @return void
  void setIndex(const IndexBuffer buffer);

  /// @brief Sets a specific buffer attribute for the geometry
  /// @param name The name of the buffer attribute to set
  /// @param buffer The buffer attribute to assign to the geometry
  /// @return void
  void setAttribute(const std::string name, const BufferAttribute buffer);

  /// @brief Draws the geometry to the current context using a program
  /// @param program The program to use to draw the geometry
  /// @return void
  void draw(Program program);

private:
  /// @brief The internal gl vertex array identifiers for a specific program
  std::unordered_map<uint32_t, uint32_t> _ids;

  /// @brief The geometry's buffer attributes
  std::unordered_map<std::string, BufferAttribute> _attributes;
};

} // namespace stem