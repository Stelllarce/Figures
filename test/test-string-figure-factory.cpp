#include "catch2/catch_all.hpp"
#include "figurelib/triangle.hpp"
#include "figurelib/circle.hpp"
#include "figurelib/rectangle.hpp"
#include "figurelib/string_to_figure_converter.hpp"
#include <limits> // for numeric limits

TEST_CASE("StringToFigureConverter class tests", "[figure_string_converter]") {
    StringToFigureConverter converter;

    SECTION("Empty string") {
        REQUIRE_THROWS_AS(converter.create_figure(""), std::invalid_argument);
    }

    SECTION("Strings with less parameters than needed") {
        REQUIRE_THROWS_AS(converter.create_figure("triangle 10 20"), std::invalid_argument);
        REQUIRE_THROWS_AS(converter.create_figure("circle"), std::invalid_argument);
        REQUIRE_THROWS_AS(converter.create_figure("rectangle 10"), std::invalid_argument);
    }

    SECTION("Strings with invalid parameters") {
        REQUIRE_THROWS_AS(converter.create_figure("triangle 10 abc 20"), std::invalid_argument);
        REQUIRE_THROWS_AS(converter.create_figure("circle abc"), std::invalid_argument);
        REQUIRE_THROWS_AS(converter.create_figure("rectangle 10 abc"), std::invalid_argument);
    }

    SECTION("Invalid figure type") {
        REQUIRE_THROWS_AS(converter.create_figure("a 10 20 30"), std::invalid_argument);
        REQUIRE_THROWS_AS(converter.create_figure("shape 10 20"), std::invalid_argument);
    }

    SECTION("Valid figure strings") {
        auto triangle = converter.create_figure("triangle 3 4 5");
        REQUIRE(triangle->to_str() == "triangle 3 4 5");

        auto circle = converter.create_figure("circle 10");
        REQUIRE(circle->to_str() == "circle 10");

        auto rectangle = converter.create_figure("rectangle 3 4");
        REQUIRE(rectangle->to_str() == "rectangle 3 4");
    }
}