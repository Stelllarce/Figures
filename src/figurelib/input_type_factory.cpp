#include "input_type_factory.hpp"

/**
 * @brief Create a figure factory
 * @param in_type The type of the factory
 * @param stream Pointer to stream, if any
 * @return A unique pointer to the created factory
 */
std::unique_ptr<FigureFactory> InputTypeFactory::create(const std::string& in_type, std::unique_ptr<std::istream> stream) {
    if (in_type == "random") {
        return std::make_unique<RandomFigureFactory>();
    }
    else if (in_type == "stream") {
        if (!stream)
            throw std::invalid_argument("No stream given");
        return std::make_unique<StreamFigureFactory>(std::move(stream));
    }
    else 
        throw std::invalid_argument("Invalid string");
    return nullptr; // This should never be reached
}