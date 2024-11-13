#pragma once
#include "figure_factory.hpp"
#include <random>
#include <type_traits>
#include <ctime>



class RandomFigureFactory: public FigureFactory {
public:
    RandomFigureFactory() = default;
    RandomFigureFactory(long seed);
    Figure* create_figure() override;
private:
    long seed = time(NULL);
};