#include "triangle.hpp"

Triangle::Triangle(double side_a, double side_b, double side_c): a(side_a), b(side_b), c(side_c) {

    if (a <= 0 || b <= 0 || c <= 0) throw std::invalid_argument("Sides cannot be negative or zero");
    if (a > MAX_OVERFLOW - c || a > MAX_OVERFLOW - b || a + b > MAX_OVERFLOW - c) throw std::overflow_error("Area will overflow");
    if (a + b <= c || a + c <= b || b + c <= a) throw std::invalid_argument("Such sides cannot form a triangle"); 
}

double Triangle::perimeter() const noexcept { return a + b + c; }

std::string Triangle::to_str() const {
    std::string output;
    output.append("triangle ");
    output.append(stringify(a) + " " + stringify(b) + " " + stringify(c));
    return output;
}

std::unique_ptr<Figure> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

bool Triangle::valid_params(double a, double b, double c) {
    return !(a <= 0 || b <= 0 || c <= 0 || 
    a > MAX_OVERFLOW - c || a > MAX_OVERFLOW - b || a + b > MAX_OVERFLOW - c ||
    a + b <= c || a + c <= b || b + c <= a);
}