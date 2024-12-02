#pragma once
#include <iostream>
#include "figure_factory.hpp"
#include "string_to_figure_converter.hpp"

/**
 * @brief Factory for creating figures from a stream
 */
class StreamFigureFactory: public FigureFactory {
public:
    StreamFigureFactory(std::unique_ptr<std::istream> stream);
    std::unique_ptr<Figure> create_figure() override;
private:
    std::unique_ptr<std::istream> is; // Refrence to the stream, as it can't be copied
};