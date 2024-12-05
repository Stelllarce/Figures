#include "catch2/catch_all.hpp"
#include "figurelib/triangle.hpp"
#include "figurelib/circle.hpp"
#include "figurelib/rectangle.hpp"
#include "figurelib/string_to_figure_converter.hpp"
#include "figurelib/random_figure_factory.hpp"
#include <limits> // for numeric limits

TEST_CASE("Triangle class tests", "[triangle]") {
    SECTION("Valid triangles") {
        REQUIRE_NOTHROW(Triangle(3, 4, 5));
        REQUIRE_NOTHROW(Triangle(5, 5, 5));
        REQUIRE_NOTHROW(Triangle(2, 2, 3));
    }

    SECTION("Invalid triangles") {
        REQUIRE_THROWS_AS(Triangle(1, 1, 3), std::invalid_argument);
        REQUIRE_THROWS_AS(Triangle(0, 4, 5), std::invalid_argument);
        REQUIRE_THROWS_AS(Triangle(3, 4, -5), std::invalid_argument);
        REQUIRE_THROWS_AS(Triangle(10, 1, 1), std::invalid_argument);
    }

    SECTION("Edge cases") {
        REQUIRE_THROWS_AS(Triangle(1, 1, 2), std::invalid_argument);
        REQUIRE_THROWS_AS(Triangle(1, 2, 1), std::invalid_argument);
        REQUIRE_THROWS_AS(Triangle(2, 1, 1), std::invalid_argument);
    }

    SECTION("Overflow") {
        REQUIRE_THROWS_AS(Triangle(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 1), std::overflow_error);
        REQUIRE_THROWS_AS(Triangle(std::numeric_limits<double>::max(), 1, std::numeric_limits<double>::max()), std::overflow_error);
        REQUIRE_THROWS_AS(Triangle(1, std::numeric_limits<double>::max(), std::numeric_limits<double>::max()), std::overflow_error);
        REQUIRE_THROWS_AS(Triangle(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max()), std::overflow_error);
    }
}

TEST_CASE("Triangle to_str method tests", "[triangle]") {
    Triangle t1(3.0, 4.0, 5.0);
    Triangle t2(5.0, 5.0, 5.0);
    Triangle t3(2.0, 2.0, 3.0);
    Triangle t4(2.5, 2.5, 3.5);

    REQUIRE(t1.to_str() == "triangle 3 4 5");
    REQUIRE(t2.to_str() == "triangle 5 5 5");
    REQUIRE(t3.to_str() == "triangle 2 2 3");
    REQUIRE(t4.to_str() == "triangle 2.5 2.5 3.5");
}

TEST_CASE("Triangle clone method tests", "[triangle]") {
    Triangle t1(3, 4, 5);
    auto t1_clone = t1.clone();
    REQUIRE(t1.to_str() == t1_clone->to_str());

    Triangle t2(5, 5, 5);
    auto t2_clone = t2.clone();
    REQUIRE(t2.to_str() == t2_clone->to_str());
}