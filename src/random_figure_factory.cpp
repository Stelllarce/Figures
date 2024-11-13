#include "random_figure_factory.hpp"
#include <iostream>

Figure* RandomFigureFactory::create_figure(long seed) {
    srand(seed);
    int random_fig = std::rand() % 3 + 1;
    FigureType fig = static_cast<FigureType>(random_fig);
    const double upper = DBL_MAX;
    const double lower = 1;
    std::uniform_real_distribution<double> unif(lower, upper);
    std::default_random_engine reng(seed);

    switch (fig)
    {
        case FigureType::Triangle:
        {
            double a = unif(reng);
            double b = unif(reng); 
            double c = unif(reng);
            while (!Triangle::valid_params(a, b, c))
            {
                a = unif(reng);
                b = unif(reng);
                c = unif(reng);
            }
            return new Triangle(a, b, c);
        }
        case FigureType::Circle:
        {
            double r = unif(reng);
            while (!Circle::valid_params(r))
                r = unif(reng);
            return new Circle(r);
        }
        case FigureType::Rectangle:
        {
            
            double a = unif(reng);
            double b = unif(reng);
            while (!Rectangle::valid_params(a, b))
            {
                a = unif(reng);
                b = unif(reng);
            }
            return new Rectangle(a, b);
        }
    }
    return nullptr;
}