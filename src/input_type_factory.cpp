#include "input_type_factory.hpp"

FigureFactory* create_factory(const std::string& stream_type, std::istream* stream) {
    if (stream_type == "random") {
        return new RandomFigureFactory();
    }
    else if (stream_type == "stream") {
        return new StreamFigureFactory(std::move(*stream));
    }
    else return nullptr;
}