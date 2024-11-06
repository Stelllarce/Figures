#pragma once

#include <stdexcept>
#include <cfloat>
#include <climits>
#include <math.h>

// Use these to make the code maintanable and change types easily
typedef int type_t;
#define MAX_OVERFLOW INT_MAX

class Figure {
public:
    virtual type_t perimeter() const = 0;
    virtual ~Figure() = default;
};