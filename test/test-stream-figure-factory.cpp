#include "catch2/catch_all.hpp"
#include "figurelib/triangle.hpp"
#include "figurelib/circle.hpp"
#include "figurelib/rectangle.hpp"
#include "figurelib/random_figure_factory.hpp"
#include "figurelib/stream_figure_factory.hpp"
#include "figurelib/input_type_factory.hpp"
#include <sstream>
#include <fstream>
#include <limits> // for numeric limits

TEST_CASE("StreamFigureFactory class tests", "[stream_figure_factory]") {

    SECTION("Generate figure from STDIN stream") {
        auto input = std::make_unique<std::istringstream>("circle 10\ntriangle 10 10 10");
        StreamFigureFactory factory(std::move(input));
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");
        std::unique_ptr<Figure> figure2 = factory.create_figure();
        REQUIRE_NOTHROW(figure2->to_str());
        REQUIRE(figure2->to_str() == "triangle 10 10 10");
    }

    SECTION("Generate figure from file stream") {
        std::ofstream outfile("test_input.txt");
        outfile << "rectangle 5 10";
        outfile.close();

        auto infile = std::make_unique<std::ifstream>("test_input.txt");
        REQUIRE(infile->is_open());

        StreamFigureFactory factory(std::move(infile));
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "rectangle 5 10");

        std::remove("test_input.txt");
    }

    SECTION("Handle invalid input from STDIN stream") {
        auto input = std::make_unique<std::istringstream>("triange 10 20 30");
        StreamFigureFactory factory(std::move(input));
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);
    }

    SECTION("Handle invalid input from file stream") {
        std::ofstream outfile("test_invalid_input.txt");
        outfile << "invalid input";
        outfile.close();

        auto infile = std::make_unique<std::ifstream>("test_invalid_input.txt");
        REQUIRE(infile->is_open());

        StreamFigureFactory factory(std::move(infile));
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);

        std::remove("test_invalid_input.txt");
    }

    SECTION("Handle end of stream or EOF") {
        auto input = std::make_unique<std::istringstream>("circle 10");
        StreamFigureFactory factory(std::move(input));
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");

        REQUIRE_THROWS_AS(factory.create_figure(), std::ios_base::failure);
    }
}
