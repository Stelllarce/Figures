#pragma once

#include <stdexcept>
#include <cfloat>
#include <climits>
#include <math.h>
#include <memory>

#include "string_converter.hpp"

// Use these to make the code maintanable and change types easily
typedef int type_t;
#define MAX_OVERFLOW INT_MAX

class Figure: public StringConverter {
public:
    virtual type_t perimeter() const = 0;
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual std::string to_str() const  = 0;
    virtual ~Figure() = default;
};