#pragma once
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
    virtual std::unique_ptr<Figure> create_figure() = 0;
    // virtual std::unique_ptr<Figure> create_figure(const std::string&);
    virtual ~FigureFactory() = default;
};