#include "triangle.hpp"

Triangle::Triangle(type_t side_a, type_t side_b, type_t side_c): a(side_a), b(side_b), c(side_c) {

    if (a <= 0 || b <= 0 || c <= 0) throw std::invalid_argument("Sides cannot be negative or zero");
    if (a > MAX_OVERFLOW - c || a > MAX_OVERFLOW - b || a + b > MAX_OVERFLOW - c) throw std::overflow_error("Area will overflow");
    if (a + b <= c || a + c <= b || b + c <= a) throw std::invalid_argument("Such sides cannot form a triangle"); 
}

type_t Triangle::perimeter() const { return a + b + c; }

std::string Triangle::to_str() const {
    std::string output;
    output.append("triangle ");
    output.append(std::to_string(a) + " " + std::to_string(b) + " " + std::to_string(c));
    return output;
}