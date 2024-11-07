#pragma once 

#include "figure.hpp"
#include "string_converter.hpp"

class Rectangle: public Figure {
public:
    Rectangle(type_t a, type_t b);
    
    type_t perimeter() const override;
    std::string to_str() const override;
    std::unique_ptr<Figure> clone() const override;
private:
    type_t a, b;
};