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
    const double a, b, c;
};