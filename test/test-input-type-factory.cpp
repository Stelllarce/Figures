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

TEST_CASE("InputTypeFactory class tests", "[input_type_factory]") {

    InputTypeFactory factory;
    SECTION("Create RandomFigureFactory with 'random' input type") {
        std::unique_ptr<FigureFactory> figureFactory = factory.create("random");
        REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);
    }

    SECTION("Create StreamFigureFactory with 'stream' input type and valid stream") {
        auto input = std::make_unique<std::istringstream>("circle 10\ntriangle 10 10 10");
        std::unique_ptr<FigureFactory> figureFactory = factory.create("stream", std::move(input));
        REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);

        std::unique_ptr<Figure> figure = figureFactory->create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");

        std::unique_ptr<Figure> figure2 = figureFactory->create_figure();
        REQUIRE_NOTHROW(figure2->to_str());
        REQUIRE(figure2->to_str() == "triangle 10 10 10");
    }

    SECTION("Create StreamFigureFactory with 'stream' input type and invalid stream") {
        auto input = std::make_unique<std::istringstream>("invalid input");
        std::unique_ptr<FigureFactory> figureFactory = factory.create("stream", std::move(input));
        REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);

        REQUIRE_THROWS_AS(figureFactory->create_figure(), std::invalid_argument);
    }

    SECTION("Handle invalid input type") {
        REQUIRE_THROWS_AS(factory.create("invalid_type"), std::invalid_argument);
    }

    SECTION("Handle missing stream for 'stream' input type") {
        REQUIRE_THROWS_AS(factory.create("stream"), std::invalid_argument);
    }

    SECTION("Create a random factory and test its functionality") {
        std::unique_ptr<FigureFactory> figureFactory = factory.create("random");
        REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);

        std::unique_ptr<Figure> figure = figureFactory->create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
    }

    SECTION("Create a stream factory and test its functionality") {
        auto input = std::make_unique<std::istringstream>("circle 10\ntriangle 10 10 10");
        std::unique_ptr<FigureFactory> figureFactory = factory.create("stream", std::move(input));
        REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);

        std::unique_ptr<Figure> figure = figureFactory->create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");

        std::unique_ptr<Figure> figure2 = figureFactory->create_figure();
        REQUIRE_NOTHROW(figure2->to_str());
        REQUIRE(figure2->to_str() == "triangle 10 10 10");
    }
}