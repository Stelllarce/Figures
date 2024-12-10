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

InputTypeFactory globalFactory;

TEST_CASE("Create RandomFigureFactory with 'random' input type", "[input_type_factory]") {
    std::unique_ptr<FigureFactory> figureFactory = globalFactory.create_factory("random");
    REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);
}

TEST_CASE("Create StreamFigureFactory with 'stream' input type and valid stream", "[input_type_factory]") {
    std::unique_ptr<FigureFactory> figureFactory = globalFactory.create_factory("stream triangle 10 10 10\ncircle 5");
    REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);

    std::unique_ptr<Figure> figure = figureFactory->create_figure();
    REQUIRE(figure != nullptr);
    REQUIRE_NOTHROW(figure->to_str());
    REQUIRE(figure->to_str() == "triangle 10 10 10");

    std::unique_ptr<Figure> figure2 = figureFactory->create_figure();
    REQUIRE_NOTHROW(figure2->to_str());
    REQUIRE(figure2->to_str() == "circle 5");
}

TEST_CASE("Handle invalid input type", "[input_type_factory]") {
    REQUIRE_THROWS_AS(globalFactory.create_factory("invalid_type"), std::invalid_argument);
}

TEST_CASE("Handle missing stream for 'stream' input type", "[input_type_factory]") {
    auto fig_factory = globalFactory.create_factory("stream");
    REQUIRE_THROWS_AS(fig_factory->create_figure(), std::invalid_argument);
}

TEST_CASE("Create a random factory and test its functionality", "[input_type_factory]") {
    std::unique_ptr<FigureFactory> figureFactory = globalFactory.create_factory("random");
    REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);

    std::unique_ptr<Figure> figure = figureFactory->create_figure();
    REQUIRE(figure != nullptr);
    REQUIRE_NOTHROW(figure->to_str());
}

TEST_CASE("Create a stream factory and test its functionality", "[input_type_factory]") {
    std::string input("stream circle 10\ntriangle 10 10 10");
    std::unique_ptr<FigureFactory> figureFactory = globalFactory.create_factory(input);
    REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);

    std::unique_ptr<Figure> figure = figureFactory->create_figure();
    REQUIRE(figure != nullptr);
    REQUIRE_NOTHROW(figure->to_str());
    REQUIRE(figure->to_str() == "circle 10");

    std::unique_ptr<Figure> figure2 = figureFactory->create_figure();
    REQUIRE_NOTHROW(figure2->to_str());
    REQUIRE(figure2->to_str() == "triangle 10 10 10");
}

TEST_CASE("Create a file stream factory and test its functionality", "[input_type_factory]") {
    std::ofstream outfile("test_figures.txt");
    outfile << "rectangle 4 5\ncircle 7";
    outfile.close();

    std::unique_ptr<FigureFactory> figureFactory = globalFactory.create_factory("file test_figures.txt");
    REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);

    std::unique_ptr<Figure> figure = figureFactory->create_figure();
    REQUIRE(figure != nullptr);
    REQUIRE_NOTHROW(figure->to_str());
    REQUIRE(figure->to_str() == "rectangle 4 5");

    std::unique_ptr<Figure> figure2 = figureFactory->create_figure();
    REQUIRE_NOTHROW(figure2->to_str());
    REQUIRE(figure2->to_str() == "circle 7");

    std::remove("test_figures.txt");
}
