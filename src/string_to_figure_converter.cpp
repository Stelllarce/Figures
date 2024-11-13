#include "string_to_figure_converter.hpp"

FigureType StringToFigureConverter::convert(const std::string& string) const {
    if (string == "triangle") return FigureType::Triangle;
    else if (string == "circle") return FigureType::Circle;
    else if (string == "rectangle") return FigureType::Rectangle;
    else return FigureType::InvalidType;
}

Figure* StringToFigureConverter::make_figure(std::string repr) {
    if (repr.empty() || !isalpha(repr[0]))
        throw std::invalid_argument("Bad string");
    
    std::stringstream stream_repr(repr);
    std::string type;
    stream_repr >> type;

    switch (convert(type))
    {
    case FigureType::Triangle:
    {
        double a = -1, b = -1, c = -1;
        stream_repr >> a >> b >> c;
        return new Triangle(a, b, c);      
    }
    case FigureType::Rectangle:
    {
        double a = -1, b = -1;
        stream_repr >> a >> b;
        return new Rectangle(a, b);
    }
    case FigureType::Circle:
    {
        double r = -1;
        stream_repr >> r;
        return new Circle(r);
    }
    case FigureType::InvalidType:
        throw std::invalid_argument("Invalid figure type");
    }
    return nullptr;
}
