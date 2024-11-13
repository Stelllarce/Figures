#include "figure_factory.hpp"
#include <random>
#include <type_traits>
#include "triangle.hpp"
#include "rectangle.hpp"
#include "circle.hpp"


class RandomFigureFactory: public FigureFactory {
public:
    Figure* create_figure(long seed = 1) override;
};