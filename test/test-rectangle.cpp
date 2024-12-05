#include "catch2/catch_all.hpp"
#include "figurelib/triangle.hpp"
#include "figurelib/circle.hpp"
#include "figurelib/rectangle.hpp"
#include "figurelib/string_to_figure_converter.hpp"
#include "figurelib/random_figure_factory.hpp"
#include <limits> // for numeric limits

TEST_CASE("Rectangle class tests", "[rectangle]") {
    SECTION("Valid rectangles") {
        REQUIRE_NOTHROW(Rectangle(3, 4));
        REQUIRE_NOTHROW(Rectangle(5, 5));
        REQUIRE_NOTHROW(Rectangle(2, 3));
    }

    SECTION("Invalid rectangles") {
        REQUIRE_THROWS_AS(Rectangle(0, 4), std::invalid_argument);
        REQUIRE_THROWS_AS(Rectangle(3, 0), std::invalid_argument);
        REQUIRE_THROWS_AS(Rectangle(-3, 4), std::invalid_argument);
        REQUIRE_THROWS_AS(Rectangle(3, -4), std::invalid_argument);
    }

    SECTION("Overflow") {
        REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<double>::max(), 1), std::overflow_error);
        REQUIRE_THROWS_AS(Rectangle(1, std::numeric_limits<double>::max()), std::overflow_error);
        REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()), std::overflow_error);
    }
}

TEST_CASE("Rectangle to_str method tests", "[rectangle]") {
    Rectangle r1(3.0, 4.0);
    Rectangle r2(5.0, 5.0);
    Rectangle r3(2.0, 3.0);
    Rectangle r4(2.5, 3.5);

    REQUIRE(r1.to_str() == "rectangle 3 4");
    REQUIRE(r2.to_str() == "rectangle 5 5");
    REQUIRE(r3.to_str() == "rectangle 2 3");
    REQUIRE(r4.to_str() == "rectangle 2.5 3.5");
}

TEST_CASE("Rectangle clone method tests", "[rectangle]") {
    Rectangle r1(3, 4);
    auto r1_clone = r1.clone();
    REQUIRE(r1.to_str() == r1_clone->to_str());

    Rectangle r2(5, 5);
    auto r2_clone = r2.clone();
    REQUIRE(r2.to_str() == r2_clone->to_str());
}