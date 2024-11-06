#include "catch2/catch_all.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
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
        REQUIRE_THROWS_AS(Triangle(std::numeric_limits<type_t>::max(), std::numeric_limits<type_t>::max(), 1), std::overflow_error);
        REQUIRE_THROWS_AS(Triangle(std::numeric_limits<type_t>::max(), 1, std::numeric_limits<type_t>::max()), std::overflow_error);
        REQUIRE_THROWS_AS(Triangle(1, std::numeric_limits<type_t>::max(), std::numeric_limits<type_t>::max()), std::overflow_error);
        REQUIRE_THROWS_AS(Triangle(std::numeric_limits<type_t>::max(), std::numeric_limits<type_t>::max(), std::numeric_limits<type_t>::max()), std::overflow_error);
    }
}

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
        REQUIRE_THROWS_AS(Circle(std::numeric_limits<type_t>::max()), std::overflow_error);
    }
}

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
        REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<type_t>::max(), 1), std::overflow_error);
        REQUIRE_THROWS_AS(Rectangle(1, std::numeric_limits<type_t>::max()), std::overflow_error);
        REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<type_t>::max(), std::numeric_limits<type_t>::max()), std::overflow_error);
    }
}

TEST_CASE("Triangle to_str method tests", "[triangle]") {
    Triangle t1(3, 4, 5);
    Triangle t2(5, 5, 5);
    Triangle t3(2, 2, 3);

    REQUIRE(t1.to_str() == "triangle 3 4 5");
    REQUIRE(t2.to_str() == "triangle 5 5 5");
    REQUIRE(t3.to_str() == "triangle 2 2 3");
}

TEST_CASE("Circle to_str method tests", "[circle]") {
    Circle c1(1);
    Circle c2(10);
    Circle c3(100);

    REQUIRE(c1.to_str() == "circle 1");
    REQUIRE(c2.to_str() == "circle 10");
    REQUIRE(c3.to_str() == "circle 100");
}

TEST_CASE("Rectangle to_str method tests", "[rectangle]") {
    Rectangle r1(3, 4);
    Rectangle r2(5, 5);
    Rectangle r3(2, 3);

    REQUIRE(r1.to_str() == "rectangle 3 4");
    REQUIRE(r2.to_str() == "rectangle 5 5");
    REQUIRE(r3.to_str() == "rectangle 2 3");
}