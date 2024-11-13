#include "figure_factory.hpp"
#include <random>
#include <type_traits>



class RandomFigureFactory: public FigureFactory {
public:
    RandomFigureFactory(long seed);
    Figure* create_figure() override;
private:
    long seed = 1;
};