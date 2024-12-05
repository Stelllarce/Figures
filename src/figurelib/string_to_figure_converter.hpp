#pragma once
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "figure.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "figure_factory.hpp"

/**
 * @brief Class for converting strings to figures
 */
class StringToFigureConverter /* : public FigureFactory */ {
public:
    std::unique_ptr<Figure> create_figure(const std::string& repr) /* override */;
private:
    FigureType enumify(const std::string& string) const;
};