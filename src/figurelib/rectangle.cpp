#include "rectangle.hpp"

/**
 * @brief Construct a new Rectangle::Rectangle object
 * @param side_a The first side of the rectangle
 * @param side_b The second side of the rectangle
 */
Rectangle::Rectangle(double side_a, double side_b): a(side_a), b(side_b) {
    if (negative_or_zero(a, b)) throw std::invalid_argument("Sides cannot be zero or negative");
    if (overflow(a, b)) throw std::overflow_error("Perimeter would overflow");
}

/**
 * @brief Calculate the perimeter of the rectangle
 * @return double The perimeter of the rectangle
 */
double Rectangle::perimeter() const noexcept { return (double)(2 * (a + b)); }

/**
 * @brief Convert the rectangle to a string
 * @return std::string The string representation of the rectangle
 */
std::string Rectangle::to_str() const {
    std::string output;
    output.append("rectangle ");

    output.append(stringify(a) + " " + stringify(b));
    return output;
}

/**
 * @brief Clone the rectangle
 * @return std::unique_ptr<Figure> A unique pointer to the cloned rectangle
 */
std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

/**
 * @brief Check if the parameters are valid
 * @param a The first side of the rectangle
 * @param b The second side of the rectangle
 * @return true If the parameters are valid
 * @return false If the parameters are invalid
 */
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