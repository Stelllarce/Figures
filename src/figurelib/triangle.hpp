#pragma once

#include "figure.hpp"
#include "string_converter.hpp"

class Triangle: public Figure {
public:
    Triangle(double a, double b, double c);

    double perimeter() const noexcept override;
    std::string to_str() const override;
    std::unique_ptr<Figure> clone() const override;
    static bool valid_params(double a, double b, double c);
private:
    static bool negative_or_zero(double a, double b, double c);
    static bool overflow(double a, double b, double c);
    static bool invalid_triangle(double a, double b, double c);
    const double a, b, c;
};