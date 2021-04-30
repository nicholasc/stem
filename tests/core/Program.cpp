#include <catch.hpp>
#include <stem/core/Program.hpp>

const std::string invalidShader = "syntax error;";
const std::string validShader = "void main() {}";

TEST_CASE("stem::Program", "[core]") {
  stem::Program program({
    .vertex = validShader,
    .fragment = validShader,
  });

  SECTION("constructor: non-zero id") {
    REQUIRE(program.getId() != 0);
  }

  SECTION("compile: empty shaders do not throw") {
    REQUIRE_NOTHROW(stem::Program());
    REQUIRE_NOTHROW(stem::Program({.vertex = ""}));
  }

  SECTION("compile: invalid shaders throw syntax errors") {
    REQUIRE_THROWS_AS(
      stem::Program({.vertex = invalidShader}), stem::ShaderSyntaxError
    );
  }

  SECTION("compile: valid shaders compile") {
    REQUIRE_NOTHROW(stem::Program({.vertex = validShader}));
  }

  SECTION("destructor: zero id") {
    program.destroy();
    REQUIRE(program.getId() == 0);
  }
}