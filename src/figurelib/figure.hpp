#pragma once

#include <stdexcept>
#include <cfloat>
#include <climits>
#include <math.h>
#include <memory>

#include "string_convertible.hpp"

const auto MAX_OVERFLOW = DBL_MAX;

/**
 * @brief Enum class for the figure types
 */
enum class FigureType {
    InvalidType,
    Circle,
    Triangle,
    Rectangle
};

/**
 * @brief Figure interface
 */
class Figure: public StringConvertible {
public:
    /**
     * @brief Calculate the perimeter of the figure
     * @return double The perimeter of the figure
     */
    virtual double perimeter() const noexcept = 0;
    /**
     * @brief Clone the figure
     * @return std::unique_ptr<Figure> A unique pointer to the cloned figure
     */
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual ~Figure() = default;
};