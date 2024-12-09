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
        std::istringstream input{"circle 10\ntriangle 10 10 10"};
        StreamFigureFactory factory(input);
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");
        std::unique_ptr<Figure> figure2 = factory.create_figure();
        REQUIRE_NOTHROW(figure2->to_str());
        REQUIRE(figure2->to_str() == "triangle 10 10 10");
    }

    SECTION("Complex case generating figure from STDIN") {
        std::istringstream input {
            "circle 10\n"
            "triangle 10 10 10\n"
            "rectangle 5 10\n"
            "circle 15\n"
            "triangle 3 4 5\n"
            "rectangle 2 4\n"
            "circle 20\n"
            "triangle 6 8 10\n"
            "rectangle 7 14\n"
            "circle 25\n"
            "triangle 5 12 13\n"
            "rectangle 8 16\n"
            "circle 30\n"
            "triangle 9 12 15\n"
            "rectangle 10 20\n"
            "circle 35\n"
            "triangle 7 24 25\n"
            "rectangle 12 24\n"
            "circle 40\n"
            "triangle 8 15 17"
        };
        StreamFigureFactory factory(input);
        std::vector<std::string> expected_figures = {
            "circle 10", "triangle 10 10 10", "rectangle 5 10", "circle 15", "triangle 3 4 5",
            "rectangle 2 4", "circle 20", "triangle 6 8 10", "rectangle 7 14", "circle 25",
            "triangle 5 12 13", "rectangle 8 16", "circle 30", "triangle 9 12 15", "rectangle 10 20",
            "circle 35", "triangle 7 24 25", "rectangle 12 24", "circle 40", "triangle 8 15 17"
        };

        for (const auto& expected : expected_figures) {
            std::unique_ptr<Figure> figure = factory.create_figure();
            REQUIRE(figure != nullptr);
            REQUIRE_NOTHROW(figure->to_str());
            REQUIRE(figure->to_str() == expected);
        }
    }

    SECTION("Generate figure from file stream") {
        std::ofstream outfile("test_input.txt");
        outfile << "rectangle 5 10";
        outfile.close();

        std::ifstream infile("test_input.txt");
        REQUIRE(infile.is_open());

        StreamFigureFactory factory(infile);
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "rectangle 5 10");

        std::remove("test_input.txt");
    }

    SECTION("Complex case generating figure from file stream") {
        std::ofstream outfile("test_complex_input.txt");
        outfile << "circle 10\n"
                << "triangle 10 10 10\n"
                << "rectangle 5 10\n"
                << "circle 15\n"
                << "triangle 3 4 5\n"
                << "rectangle 2 4\n"
                << "circle 20\n"
                << "triangle 6 8 10\n"
                << "rectangle 7 14\n"
                << "circle 25\n"
                << "triangle 5 12 13\n"
                << "rectangle 8 16\n"
                << "circle 30\n"
                << "triangle 9 12 15\n"
                << "rectangle 10 20\n"
                << "circle 35\n"
                << "triangle 7 24 25\n"
                << "rectangle 12 24\n"
                << "circle 40\n"
                << "triangle 8 15 17";
        outfile.close();

        std::ifstream infile("test_complex_input.txt");
        REQUIRE(infile.is_open());

        StreamFigureFactory factory(infile);
        std::vector<std::string> expected_figures = {
            "circle 10", "triangle 10 10 10", "rectangle 5 10", "circle 15", "triangle 3 4 5",
            "rectangle 2 4", "circle 20", "triangle 6 8 10", "rectangle 7 14", "circle 25",
            "triangle 5 12 13", "rectangle 8 16", "circle 30", "triangle 9 12 15", "rectangle 10 20",
            "circle 35", "triangle 7 24 25", "rectangle 12 24", "circle 40", "triangle 8 15 17"
        };

        for (const auto& expected : expected_figures) {
            std::unique_ptr<Figure> figure = factory.create_figure();
            REQUIRE(figure != nullptr);
            REQUIRE_NOTHROW(figure->to_str());
            REQUIRE(figure->to_str() == expected);
        }

        std::remove("test_complex_input.txt");
    }

    SECTION("Handle invalid input from STDIN stream") {
        std::istringstream istream("triange 10 20 30");
        StreamFigureFactory factory(istream);
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

        std::remove("test_invalid_input.txt");
    }

    SECTION("Handle end of stream or EOF") {
        std::istringstream istream("circle 10");
        StreamFigureFactory factory(istream);
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");

        REQUIRE_THROWS_AS(factory.create_figure(), std::ios_base::failure);
    }

    SECTION("Handle trailing characters after valid figure") {
        std::istringstream istream("circle 10\n");
        StreamFigureFactory factory(istream);
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);
    }
}
