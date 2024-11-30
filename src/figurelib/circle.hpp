#pragma once

#include "figure.hpp"
#include "string_converter.hpp"


class Circle: public Figure{
public:
    Circle(double rad);
    
    double perimeter() const noexcept override;
    std::string to_str() const override;
    std::unique_ptr<Figure> clone() const override;
    static bool valid_params(double r);
private:
    static constexpr double PI = 3.14159265358979323846; 
    const double r;
};