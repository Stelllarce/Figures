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