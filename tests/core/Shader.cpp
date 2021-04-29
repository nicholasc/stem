#include <catch.hpp>
#include <stem/core/Shader.hpp>

TEST_CASE("stem::Shader class", "[core]") {
  stem::VertexShader vertex;

  SECTION("id is non zero after constructor") {
    REQUIRE(vertex.getId() != 0);
  }

  SECTION("empty shader does not compile") {
    REQUIRE_THROWS_AS(vertex.compile(), stem::ShaderSyntaxError);
  }

  SECTION("invalid shader does not compile") {
    vertex.setSource("syntax error;");
    REQUIRE_THROWS_AS(vertex.compile(), stem::ShaderSyntaxError);
  }

  SECTION("valid shader does compile") {
    vertex.setSource("void main() { }");
    vertex.compile();
  }

  SECTION("id is zero after destroy") {
    vertex.destroy();
    REQUIRE(vertex.getId() == 0);
  }
}