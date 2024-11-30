#include "input_type_factory.hpp"

std::unique_ptr<FigureFactory> InputTypeFactory::create(const std::string& in_type, std::istream* stream) {
    if (in_type == "random") {
        return std::make_unique<RandomFigureFactory>();
    }
    else if (in_type == "stream") {
        if (!stream)
            throw std::invalid_argument("No stream given");
        return std::make_unique<StreamFigureFactory>(std::move(*stream));
    }
    else 
        throw std::invalid_argument("Invalid string");
    return nullptr;
}