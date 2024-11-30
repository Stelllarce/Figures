#pragma once

#include <stdexcept>
#include <cfloat>
#include <climits>
#include <math.h>
#include <memory>

#include "string_converter.hpp"

#define MAX_OVERFLOW DBL_MAX

enum class FigureType {
    InvalidType,
    Circle,
    Triangle,
    Rectangle
};

class Figure: public StringConverter {
public:
    virtual double perimeter() const noexcept = 0;
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual std::string to_str() const  = 0;
    virtual ~Figure() = default;
};