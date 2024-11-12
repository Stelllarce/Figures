#include "catch2/catch_all.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "figure_string_converter.hpp"
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

TEST_CASE("Triangle clone method tests", "[triangle]") {
    Triangle t1(3, 4, 5);
    auto t1_clone = t1.clone();
    REQUIRE(t1.to_str() == t1_clone->to_str());

    Triangle t2(5, 5, 5);
    auto t2_clone = t2.clone();
    REQUIRE(t2.to_str() == t2_clone->to_str());
}

TEST_CASE("Circle clone method tests", "[circle]") {
    Circle c1(1);
    auto c1_clone = c1.clone();
    REQUIRE(c1.to_str() == c1_clone->to_str());

    Circle c2(10);
    auto c2_clone = c2.clone();
    REQUIRE(c2.to_str() == c2_clone->to_str());
}

TEST_CASE("Rectangle clone method tests", "[rectangle]") {
    Rectangle r1(3, 4);
    auto r1_clone = r1.clone();
    REQUIRE(r1.to_str() == r1_clone->to_str());

    Rectangle r2(5, 5);
    auto r2_clone = r2.clone();
    REQUIRE(r2.to_str() == r2_clone->to_str());
}
