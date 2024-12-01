#include "random_figure_factory.hpp"

/**
 * @brief Construct a new RandomFigureFactory::RandomFigureFactory object
 * @param seed The seed for the random number generator, used for static seeding for tests
 */
RandomFigureFactory::RandomFigureFactory(long seed): seed(seed) {
    std::srand(seed); // Seed the random number generator
}

/**
 * @brief Create a random figure
 * @return std::unique_ptr<Figure> A unique pointer to the created figure
 */
std::unique_ptr<Figure> RandomFigureFactory::create_figure() {
    int random_fig = std::rand() % 3 + 1; // Random number between 1 and 3 for enum class
    FigureType fig = static_cast<FigureType>(random_fig); // Convert to enum class
    const double upper = 1.0 + 10E3; // Upper limit for random double generation
    const double lower = 1.0; // Lower limit for random double generation

    auto random_double = [lower, upper]() {
        return lower + static_cast<double>(std::rand()) / RAND_MAX * (upper - lower);
    };

    switch (fig)
    {
        case FigureType::Triangle:
        {
            double a = random_double();
            double b = random_double(); 
            double c = random_double();
            while (!Triangle::valid_params(a, b, c)) // Create values until valid
            {
                a = random_double();
                b = random_double();
                c = random_double();
            }
            return std::make_unique<Triangle>(a, b, c);
        }
        case FigureType::Circle:
        {
            double r = random_double();
            while (!Circle::valid_params(r)) // Create values until valid
                r = random_double();
            return std::make_unique<Circle>(r);
        }
        case FigureType::Rectangle:
        {
            double a = random_double();
            double b = random_double();
            while (!Rectangle::valid_params(a, b)) // Create values until valid
            {
                a = random_double();
                b = random_double();
            }
            return std::make_unique<Rectangle>(a, b);
        }
    }
    return nullptr; // This should never be reached
}