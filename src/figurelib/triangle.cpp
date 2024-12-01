#include "triangle.hpp"

/**
 * @brief Construct a new Triangle::Triangle object
 * @param side_a The first side of the triangle
 * @param side_b The second side of the triangle
 * @param side_c The third side of the triangle
 */
Triangle::Triangle(double side_a, double side_b, double side_c): a(side_a), b(side_b), c(side_c) {

    if (negative_or_zero(a, b, c)) throw std::invalid_argument("Sides cannot be negative or zero");
    if (overflow(a, b, c)) throw std::overflow_error("Area will overflow");
    if (invalid_triangle(a, b, c)) throw std::invalid_argument("Such sides cannot form a triangle"); 
}

/**
 * @brief Calculate the perimeter of the triangle
 * @return double The perimeter of the triangle
 */
double Triangle::perimeter() const noexcept { return a + b + c; }

/**
 * @brief Convert the triangle to a string
 * @return std::string The string representation of the triangle
 */
std::string Triangle::to_str() const {
    std::string output;
    output.append("triangle ");
    output.append(stringify(a) + " " + stringify(b) + " " + stringify(c));
    return output;
}

/**
 * @brief Clone the triangle
 * @return std::unique_ptr<Figure> A unique pointer to the cloned triangle
 */
std::unique_ptr<Figure> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

/**
 * @brief Check if the parameters are valid
 * @param a The first side of the triangle
 * @param b The second side of the triangle
 * @param c The third side of the triangle
 * @return true If the parameters are valid
 * @return false If the parameters are invalid
 */
bool Triangle::negative_or_zero(double a, double b, double c) {
    return a <= 0 || b <= 0 || c <= 0;
}

bool Triangle::overflow(double a, double b, double c) {
    return a > MAX_OVERFLOW - c || a > MAX_OVERFLOW - b || a + b > MAX_OVERFLOW - c;
}

bool Triangle::invalid_triangle(double a, double b, double c) {
    return a + b <= c || a + c <= b || b + c <= a;
}

bool Triangle::valid_params(double a, double b, double c) {
    return !(negative_or_zero(a, b, c) || 
            overflow(a, b, c) ||
            invalid_triangle(a, b, c));
}