#pragma once 

#include "figure.hpp"
#include "string_converter.hpp"

class Rectangle: public Figure {
public:
    Rectangle(double a, double b);
    
    double perimeter() const noexcept override;
    std::string to_str() const override;
    std::unique_ptr<Figure> clone() const override;
    static bool valid_params(double a, double b);
private:
    double a, b;
};