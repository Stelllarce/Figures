#include "string_to_figure_converter.hpp"

/**
 * @brief Convert a string to a figure enum type
 * @param string The string to convert
 * @return FigureType The converted figure type
 */
FigureType StringToFigureConverter::enumify(const std::string& string) const {
    if (string == "triangle") return FigureType::Triangle;
    else if (string == "circle") return FigureType::Circle;
    else if (string == "rectangle") return FigureType::Rectangle;
    else return FigureType::InvalidType;
}

/**
 * @brief Convert a string to a figure
 * @param repr The string to convert
 * @return std::unique_ptr<Figure> A unique pointer to the created figure
 */
std::unique_ptr<Figure> StringToFigureConverter::make_figure(const std::string& repr) {
    if (repr.empty() || !isalpha(repr[0]))
        throw std::invalid_argument("Bad string");
    
    std::stringstream stream_repr(std::move(repr));
    std::string type;
    stream_repr >> type;

    switch (enumify(type))
    {
    case FigureType::Triangle:
    {
        double a = -1, b = -1, c = -1;
        stream_repr >> a >> b >> c;
        return std::make_unique<Triangle>(a, b, c);      
    }
    case FigureType::Rectangle:
    {
        double a = -1, b = -1;
        stream_repr >> a >> b;
        return std::make_unique<Rectangle>(a, b);
    }
    case FigureType::Circle:
    {
        double r = -1;
        stream_repr >> r;
        return std::make_unique<Circle>(r);
    }
    case FigureType::InvalidType:
        throw std::invalid_argument("Invalid figure type");
    }
    return nullptr;
}
