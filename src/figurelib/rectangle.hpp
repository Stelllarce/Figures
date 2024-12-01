#pragma once 

#include "figure.hpp"
#include "string_converter.hpp"

/**
 * @brief Rectangle class
 */
class Rectangle: public Figure {
public:
    Rectangle(double a, double b);
    
    double perimeter() const noexcept override;
    std::string to_str() const override;
    std::unique_ptr<Figure> clone() const override;
    static bool valid_params(double a, double b);
private:
    static bool negative_or_zero(double a, double b);
    static bool overflow(double a, double b);
    const double a, b;
};