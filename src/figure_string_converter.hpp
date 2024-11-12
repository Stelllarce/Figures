#pragma once
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "figure.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

enum class FigureType {
    InvalidType,
    Circle,
    Triangle,
    Rectangle
};

class FigureStringConverter {
public:
    Figure* make_figure(std::string repr);
private:
    FigureType convert(const std::string& string) const;
};