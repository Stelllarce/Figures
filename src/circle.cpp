#include "circle.hpp"

Circle::Circle(type_t rad): r(rad) {
    if (r <= 0) throw std::invalid_argument("Radius can't be negative or zero");
    if (r > MAX_OVERFLOW / (2 * PI)) throw std::overflow_error("Perimeter overflow");
}

type_t Circle::perimeter() const { return (type_t)(2 * r * PI); }

std::string Circle::to_str() const {
    std::string output;
    output.append("circle ");
    output.append(std::to_string(r));
    return output;
}

std::unique_ptr<Figure> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}