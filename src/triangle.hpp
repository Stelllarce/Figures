#pragma once

#include "figure.hpp"
#include "string_converter.hpp"

class Triangle: public Figure {
public:
    Triangle(type_t a, type_t b, type_t c);

    type_t perimeter() const override;
    std::string to_str() const override;
    std::unique_ptr<Figure> clone() const override;
private:
    const type_t a, b, c;
};