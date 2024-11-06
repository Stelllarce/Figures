#pragma once 

#include "figure.hpp"
#include "string_converter.hpp"

class Rectangle: public Figure, public StringConverter {
public:
    Rectangle(type_t a, type_t b);
    Rectangle(const Rectangle&) = delete;
    Rectangle(Rectangle&&) = delete;
    
    type_t perimeter() const override;
    std::string to_str() const override;
private:
    type_t a, b;
};