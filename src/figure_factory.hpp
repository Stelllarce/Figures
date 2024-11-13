#include "figure.hpp"

class FigureFactory {
public:
    virtual Figure* create_figure(long seed = 1) = 0;
    virtual ~FigureFactory() = default;
};