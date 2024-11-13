#include "catch2/catch_all.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "random_figure_factory.hpp"
#include <limits> // for numeric limits

TEST_CASE("RandomFigureFactory class tests", "[random_figure_factory]") {
    RandomFigureFactory factory;

    SECTION("Generate random figures with fixed seed") {
        Figure* figure1 = factory.create_figure(12345);
        REQUIRE(figure1 != nullptr);
        REQUIRE_NOTHROW(figure1->to_str());

        Figure* figure2 = factory.create_figure(67890);
        REQUIRE(figure2 != nullptr);
        REQUIRE_NOTHROW(figure2->to_str());

        Figure* figure3 = factory.create_figure(54321);
        REQUIRE(figure3 != nullptr);
        REQUIRE_NOTHROW(figure3->to_str());

        Figure* figure4 = factory.create_figure(98765);
        REQUIRE(figure4 != nullptr);
        REQUIRE_NOTHROW(figure4->to_str());
    }

    SECTION("Generate same figure with same seed") {
        Figure* figure1 = factory.create_figure(12345);
        Figure* figure2 = factory.create_figure(12345);
        REQUIRE(figure1->to_str() == figure2->to_str());

        Figure* figure3 = factory.create_figure(67890);
        Figure* figure4 = factory.create_figure(67890);
        REQUIRE(figure3->to_str() == figure4->to_str());
    }

    SECTION("Generate different figures with different seeds") {
        Figure* figure1 = factory.create_figure(12345);
        Figure* figure2 = factory.create_figure(67890);
        REQUIRE(figure1->to_str() != figure2->to_str());

        Figure* figure3 = factory.create_figure(54321);
        Figure* figure4 = factory.create_figure(98765);
        REQUIRE(figure3->to_str() != figure4->to_str());
    }
}