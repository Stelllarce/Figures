#pragma once

#include "figure.hpp"
#include "string_converter.hpp"

static constexpr double PI = 3.14159265358979323846; 

class Circle: public Figure, public StringConverter {
public:
    Circle(type_t rad);
    Circle(const Circle&) = delete;
    Circle(Circle&&) = delete;
    
    type_t perimeter() const override;
    std::string to_str() const override;
private:
    const type_t r;
};