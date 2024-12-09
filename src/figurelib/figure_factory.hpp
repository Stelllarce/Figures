#pragma once
#include <stdexcept>
#include "figure.hpp"
#include "triangle.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

/**
 * @brief Factory interface for creating figures
 */
class FigureFactory {
public:
    /**
     * @brief Create a figure
     * @return std::unique_ptr<Figure> A unique pointer to the created figure
     */
    virtual std::unique_ptr<Figure> create_figure() { throw std::logic_error("Figure factory is not meant to call this function"); }
    virtual std::unique_ptr<Figure> create_figure(const std::string&) { throw std::logic_error("Figure factory is not meant to call this function"); }
    virtual ~FigureFactory() = default;
};