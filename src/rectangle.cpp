#include "rectangle.hpp"

Rectangle::Rectangle(type_t side_a, type_t side_b): a(side_a), b(side_b) {
    if (a <= 0 || b <= 0) throw std::invalid_argument("Sides cannot be zero or negative");
    if (a > (MAX_OVERFLOW - (2 * b)) / 2 || b > (MAX_OVERFLOW - (2 * a)) / 2) throw std::overflow_error("Perimeter would overflow");
}

type_t Rectangle::perimeter() const { return (type_t)(2 * (a + b)); }

std::string Rectangle::to_str() const {
    std::string output;
    output.append("rectangle ");
    output.append(std::to_string(a) + " " + std::to_string(b));
    return output;
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}