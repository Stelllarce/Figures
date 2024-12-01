#include "rectangle.hpp"

Rectangle::Rectangle(double side_a, double side_b): a(side_a), b(side_b) {
    if (negative_or_zero(a, b)) throw std::invalid_argument("Sides cannot be zero or negative");
    if (overflow(a, b)) throw std::overflow_error("Perimeter would overflow");
}

double Rectangle::perimeter() const noexcept { return (double)(2 * (a + b)); }

std::string Rectangle::to_str() const {
    std::string output;
    output.append("rectangle ");

    output.append(stringify(a) + " " + stringify(b));
    return output;
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

bool Rectangle::negative_or_zero(double a, double b) {
    return a <= 0 || b <= 0;
}

bool Rectangle::overflow(double a, double b) {
    return a > MAX_OVERFLOW - (2 * b) || b > MAX_OVERFLOW - (2 * a);
}

bool Rectangle::valid_params(double a, double b) {
    return !(negative_or_zero(a, b) || 
            overflow(a, b)
            );
}