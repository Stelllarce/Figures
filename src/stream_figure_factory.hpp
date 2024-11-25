#pragma once
#include <iostream>
#include "figure_factory.hpp"
#include "string_to_figure_converter.hpp"

class StreamFigureFactory: public FigureFactory {
public:
    StreamFigureFactory(std::istream&& stream);
    Figure* create_figure() override;
private:
    std::istream& is;
};