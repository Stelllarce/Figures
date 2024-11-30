#pragma once
#include "figure.hpp"
#include "triangle.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

class FigureFactory {
public:
    virtual std::unique_ptr<Figure> create_figure() = 0;
    virtual ~FigureFactory() = default;
};