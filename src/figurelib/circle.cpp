#include "circle.hpp"

Circle::Circle(double rad): r(rad) {
    if (negative_or_zero(r)) throw std::invalid_argument("Radius can't be negative or zero");
    if (overflow(r)) throw std::overflow_error("Perimeter overflow");
}

double Circle::perimeter() const noexcept { return (double)(2 * r * PI); }

std::string Circle::to_str() const {
    std::string output;
    output.append("circle ");
    output.append(stringify(r));
    return output;
}

std::unique_ptr<Figure> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

bool Circle::negative_or_zero(double r) {
    return r <= 0;
}

bool Circle::overflow(double r) {
    return r > MAX_OVERFLOW / (2 * PI);
}

bool Circle::valid_params(double r) {
    return !(negative_or_zero(r) || overflow(r));
}