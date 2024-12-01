#include "random_figure_factory.hpp"
#include <iostream>

/**
 * @brief Construct a new RandomFigureFactory::RandomFigureFactory object
 * @param seed The seed for the random number generator, used for static seeding for tests
 */
RandomFigureFactory::RandomFigureFactory(long seed): seed(seed) {}

/**
 * @brief Create a random figure
 * @return std::unique_ptr<Figure> A unique pointer to the created figure
 */
std::unique_ptr<Figure> RandomFigureFactory::create_figure() {
    srand(seed); // Seed the random number generator
    int random_fig = std::rand() % 3 + 1; // Random number between 1 and 3 for enum class
    FigureType fig = static_cast<FigureType>(random_fig); // Convert to enum class
    const double upper = DBL_MAX; // Upper limit for random double generation
    const double lower = 1; // Lower limit for random double generation
    std::uniform_real_distribution<double> unif(lower, upper); // Uniform distribution for random double generation
    std::default_random_engine reng(seed); // Random engine for seeding

    switch (fig)
    {
        case FigureType::Triangle:
        {
            double a = unif(reng);
            double b = unif(reng); 
            double c = unif(reng);
            while (!Triangle::valid_params(a, b, c)) // Create values until valid
            {
                a = unif(reng);
                b = unif(reng);
                c = unif(reng);
            }
            return std::make_unique<Triangle>(a, b, c);
        }
        case FigureType::Circle:
        {
            double r = unif(reng);
            while (!Circle::valid_params(r)) // Create values until valid
                r = unif(reng);
            return std::make_unique<Circle>(r);
        }
        case FigureType::Rectangle:
        {
            
            double a = unif(reng);
            double b = unif(reng);
            while (!Rectangle::valid_params(a, b)) // Create values until valid
            {
                a = unif(reng);
                b = unif(reng);
            }
            return std::make_unique<Rectangle>(a, b);
        }
    }
    return nullptr; // This should never be reached
}