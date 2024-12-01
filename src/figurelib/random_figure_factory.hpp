#pragma once
#include "figure_factory.hpp"
#include <random>
#include <ctime>
#include <cstdlib>

class RandomFigureFactory: public FigureFactory {
public:
    RandomFigureFactory() = default;
    RandomFigureFactory(long seed);
    std::unique_ptr<Figure> create_figure() override;
private:
    long seed = time(NULL);
};