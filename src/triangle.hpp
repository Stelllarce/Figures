#pragma once

#include "figure.hpp"
#include "string_converter.hpp"

class Triangle: private Figure, private StringConverter {
public:
    Triangle(type_t a, type_t b, type_t c);
    Triangle(const Triangle&) = delete;
    Triangle(Triangle&&) = delete;

    type_t perimeter() const override;
    std::string to_str() const override;
private:
    const type_t a, b, c;
};