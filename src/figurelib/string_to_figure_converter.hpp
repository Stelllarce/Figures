#pragma once
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "figure.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

/**
 * @brief Class for converting strings to figures
 */
class StringToFigureConverter {
public:
    std::unique_ptr<Figure> make_figure(const std::string& repr);
private:
    FigureType enumify(const std::string& string) const;
};