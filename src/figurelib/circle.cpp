#include "circle.hpp"

/**
 * @brief Construct a new Circle::Circle object
 * @param rad The radius of the circle
 */
Circle::Circle(double rad): r(rad) {
    if (negative_or_zero(r)) throw std::invalid_argument("Radius can't be negative or zero");
    if (overflow(r)) throw std::overflow_error("Perimeter overflow");
}

/**
 * @brief Calculate the perimeter of the circle
 * @return double The perimeter of the circle
 */
double Circle::perimeter() const noexcept { return (double)(2 * r * PI); }

/**
 * @brief Convert the circle to a string
 * @return std::string The string representation of the circle
 */
std::string Circle::to_str() const {
    std::string output;
    output.append("circle ");
    output.append(stringify(r));
    return output;
}

/**
 * @brief Clone the circle
 * @return std::unique_ptr<Figure> A unique pointer to the cloned circle
 */
std::unique_ptr<Figure> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

/**
 * @brief Check if the parameters are valid
 * @param r The radius of the circle
 * @return true If the parameters are valid
 * @return false If the parameters are invalid
 */
bool Circle::negative_or_zero(double r) {
    return r <= 0;
}

bool Circle::overflow(double r) {
    return r > MAX_OVERFLOW / (2 * PI);
}

bool Circle::valid_params(double r) {
    return !(negative_or_zero(r) || overflow(r));
}