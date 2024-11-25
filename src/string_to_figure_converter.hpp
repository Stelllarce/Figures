#pragma once
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "figure.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

class StringToFigureConverter {
public:
    Figure* make_figure(const std::string& repr);
private:
    FigureType enumify(const std::string& string) const;
};