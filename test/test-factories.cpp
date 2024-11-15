#include "catch2/catch_all.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "random_figure_factory.hpp"
#include "stream_figure_factory.hpp"
#include <sstream>
#include <fstream>
#include <limits> // for numeric limits

TEST_CASE("RandomFigureFactory class tests", "[random_figure_factory]") {

    SECTION("Generate random figures with fixed seed") {
        RandomFigureFactory factory1(12345);
        Figure* figure1 = factory1.create_figure();
        REQUIRE(figure1 != nullptr);
        REQUIRE_NOTHROW(figure1->to_str());

        RandomFigureFactory factory2(67890);
        Figure* figure2 = factory2.create_figure();
        REQUIRE(figure2 != nullptr);
        REQUIRE_NOTHROW(figure2->to_str());

        RandomFigureFactory factory3(54321);
        Figure* figure3 = factory3.create_figure();
        REQUIRE(figure3 != nullptr);
        REQUIRE_NOTHROW(figure3->to_str());

        RandomFigureFactory factory4(98765);
        Figure* figure4 = factory4.create_figure();
        REQUIRE(figure4 != nullptr);
        REQUIRE_NOTHROW(figure4->to_str());
    }

    SECTION("Generate same figure with same seed") {
        RandomFigureFactory factory1(12345);
        Figure* figure1 = factory1.create_figure();

        RandomFigureFactory factory2(12345);
        Figure* figure2 = factory2.create_figure();
        REQUIRE(figure1->to_str() == figure2->to_str());

        RandomFigureFactory factory3(67890);
        Figure* figure3 = factory3.create_figure();

        RandomFigureFactory factory4(67890);
        Figure* figure4 = factory4.create_figure();
        REQUIRE(figure3->to_str() == figure4->to_str());
    }

    SECTION("Generate different figures with different seeds") {
        RandomFigureFactory factory1(12345);
        Figure* figure1 = factory1.create_figure();

        RandomFigureFactory factory2(67890);
        Figure* figure2 = factory2.create_figure();
        REQUIRE(figure1->to_str() != figure2->to_str());

        RandomFigureFactory factory3(54321);
        Figure* figure3 = factory3.create_figure();

        RandomFigureFactory factory4(98765);
        Figure* figure4 = factory4.create_figure();
        REQUIRE(figure3->to_str() != figure4->to_str());
    }
}

TEST_CASE("StreamFigureFactory class tests", "[stream_figure_factory]") {

    SECTION("Generate figure from STDIN stream") {
        std::istringstream input("circle 10\ntriangle 10 10 10");
        StreamFigureFactory factory(input);
        Figure* figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");
        Figure* figure2 = factory.create_figure();
        REQUIRE_NOTHROW(figure2->to_str());
        REQUIRE(figure2->to_str() == "triangle 10 10 10");
    }

    SECTION("Generate figure from file stream") {
        std::ofstream outfile("test_input.txt");
        outfile << "rectangle 5 10";
        outfile.close();

        std::ifstream infile("test_input.txt");
        REQUIRE(infile.is_open());

        StreamFigureFactory factory(infile);
        Figure* figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "rectangle 5 10");

        infile.close();
        std::remove("test_input.txt");
    }

    SECTION("Handle invalid input from STDIN stream") {
        std::istringstream input("triange 10 20 30");
        StreamFigureFactory factory(input);
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);
    }

    SECTION("Handle invalid input from file stream") {
        std::ofstream outfile("test_invalid_input.txt");
        outfile << "invalid input";
        outfile.close();

        std::ifstream infile("test_invalid_input.txt");
        REQUIRE(infile.is_open());

        StreamFigureFactory factory(infile);
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);

        infile.close();
    }
    SECTION("Handle end of stream or EOF") {
        std::istringstream input("circle 10");
        StreamFigureFactory factory(input);
        Figure* figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");

        REQUIRE_THROWS_AS(factory.create_figure(), std::ios_base::failure);
    }
}