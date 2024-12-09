#pragma once
#include <iostream>
#include <fstream>
#include "figure_factory.hpp"
#include "string_to_figure_converter.hpp"

/**
 * @brief Factory for creating figures from a stream
 */
class StreamFigureFactory: public FigureFactory {
public:
    StreamFigureFactory(std::istream& stream);
    StreamFigureFactory(std::ifstream& stream);
    std::unique_ptr<Figure> create_figure() override;
private:
    std::istream& is;
    std::ifstream ifs;
};