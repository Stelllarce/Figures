#include "catch2/catch_all.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "random_figure_factory.hpp"
#include "stream_figure_factory.hpp"
#include "input_type_factory.hpp"
#include <sstream>
#include <fstream>
#include <limits> // for numeric limits

TEST_CASE("RandomFigureFactory class tests", "[random_figure_factory]") {

    SECTION("Generate random figures with fixed seed") {
        RandomFigureFactory factory1(12345);
        std::unique_ptr<Figure> figure1 = factory1.create_figure();
        REQUIRE(figure1 != nullptr);
        REQUIRE_NOTHROW(figure1->to_str());

        RandomFigureFactory factory2(67890);
        std::unique_ptr<Figure> figure2 = factory2.create_figure();
        REQUIRE(figure2 != nullptr);
        REQUIRE_NOTHROW(figure2->to_str());

        RandomFigureFactory factory3(54321);
        std::unique_ptr<Figure> figure3 = factory3.create_figure();
        REQUIRE(figure3 != nullptr);
        REQUIRE_NOTHROW(figure3->to_str());

        RandomFigureFactory factory4(98765);
        std::unique_ptr<Figure> figure4 = factory4.create_figure();
        REQUIRE(figure4 != nullptr);
        REQUIRE_NOTHROW(figure4->to_str());
    }

    SECTION("Generate same figure with same seed") {
        RandomFigureFactory factory1(12345);
        std::unique_ptr<Figure> figure1 = factory1.create_figure();

        RandomFigureFactory factory2(12345);
        std::unique_ptr<Figure> figure2 = factory2.create_figure();
        REQUIRE(figure1->to_str() == figure2->to_str());

        RandomFigureFactory factory3(67890);
        std::unique_ptr<Figure> figure3 = factory3.create_figure();

        RandomFigureFactory factory4(67890);
        std::unique_ptr<Figure> figure4 = factory4.create_figure();
        REQUIRE(figure3->to_str() == figure4->to_str());
    }

    SECTION("Generate different figures with different seeds") {
        RandomFigureFactory factory1(12345);
        std::unique_ptr<Figure> figure1 = factory1.create_figure();

        RandomFigureFactory factory2(67890);
        std::unique_ptr<Figure> figure2 = factory2.create_figure();
        REQUIRE(figure1->to_str() != figure2->to_str());

        RandomFigureFactory factory3(54321);
        std::unique_ptr<Figure> figure3 = factory3.create_figure();

        RandomFigureFactory factory4(98765);
        std::unique_ptr<Figure> figure4 = factory4.create_figure();
        REQUIRE(figure3->to_str() != figure4->to_str());
    }
}

TEST_CASE("StreamFigureFactory class tests", "[stream_figure_factory]") {

    SECTION("Generate figure from STDIN stream") {
        std::istringstream input("circle 10\ntriangle 10 10 10");
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

        std::ifstream infile("test_input.txt");
        REQUIRE(infile.is_open());

        StreamFigureFactory factory(std::move(infile));
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "rectangle 5 10");

        infile.close();
        std::remove("test_input.txt");
    }

    SECTION("Handle invalid input from STDIN stream") {
        std::istringstream input("triange 10 20 30");
        StreamFigureFactory factory(std::move(input));
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);
    }

    SECTION("Handle invalid input from file stream") {
        std::ofstream outfile("test_invalid_input.txt");
        outfile << "invalid input";
        outfile.close();

        std::ifstream infile("test_invalid_input.txt");
        REQUIRE(infile.is_open());

        StreamFigureFactory factory(std::move(infile));
        REQUIRE_THROWS_AS(factory.create_figure(), std::invalid_argument);

        infile.close();
    }
    SECTION("Handle end of stream or EOF") {
        std::istringstream input("circle 10");
        StreamFigureFactory factory(std::move(input));
        std::unique_ptr<Figure> figure = factory.create_figure();
        REQUIRE(figure != nullptr);
        REQUIRE_NOTHROW(figure->to_str());
        REQUIRE(figure->to_str() == "circle 10");

        REQUIRE_THROWS_AS(factory.create_figure(), std::ios_base::failure);
    }
    

}

TEST_CASE("InputTypeFactory class tests", "[input_type_factory]") {

    InputTypeFactory factory;
    SECTION("Create RandomFigureFactory with 'random' input type") {
        std::unique_ptr<FigureFactory> figureFactory = factory.create("random");
        REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);
    }

    SECTION("Create StreamFigureFactory with 'stream' input type and valid stream") {
        std::istringstream input("circle 10\ntriangle 10 10 10");
        std::unique_ptr<FigureFactory> figureFactory = factory.create("stream", &input);
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
        std::istringstream input("invalid input");
        std::unique_ptr<FigureFactory> figureFactory = factory.create("stream", &input);
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
        std::istringstream input("circle 10\ntriangle 10 10 10");
        std::unique_ptr<FigureFactory> figureFactory = factory.create("stream", &input);
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