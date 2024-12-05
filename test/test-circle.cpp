#include "catch2/catch_all.hpp"
#include "figurelib/triangle.hpp"
#include "figurelib/circle.hpp"
#include "figurelib/rectangle.hpp"
#include "figurelib/string_to_figure_converter.hpp"
#include "figurelib/random_figure_factory.hpp"
#include <limits> // for numeric limits

TEST_CASE("Circle class tests", "[circle]") {
    SECTION("Valid circles") {
        REQUIRE_NOTHROW(Circle(1));
        REQUIRE_NOTHROW(Circle(10));
        REQUIRE_NOTHROW(Circle(100));
    }

    SECTION("Invalid circles") {
        REQUIRE_THROWS_AS(Circle(0), std::invalid_argument);
        REQUIRE_THROWS_AS(Circle(-1), std::invalid_argument);
        REQUIRE_THROWS_AS(Circle(-100), std::invalid_argument);
    }

    SECTION("Overflow") {
        REQUIRE_THROWS_AS(Circle(std::numeric_limits<double>::max()), std::overflow_error);
    }
}

TEST_CASE("Circle to_str method tests", "[circle]") {
    Circle c1(1.0);
    Circle c2(10.0);
    Circle c3(100.0);
    Circle c4(2.5);

    REQUIRE(c1.to_str() == "circle 1");
    REQUIRE(c2.to_str() == "circle 10");
    REQUIRE(c3.to_str() == "circle 100");
    REQUIRE(c4.to_str() == "circle 2.5");
}

TEST_CASE("Circle clone method tests", "[circle]") {
    Circle c1(1);
    auto c1_clone = c1.clone();
    REQUIRE(c1.to_str() == c1_clone->to_str());

    Circle c2(10);
    auto c2_clone = c2.clone();
    REQUIRE(c2.to_str() == c2_clone->to_str());
}