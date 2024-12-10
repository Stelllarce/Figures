#include "input_type_factory.hpp"

/**
 * @brief Create a figure factory
 * @param in_type The type of the factory
 * @param stream Pointer to stream, if any
 * @return A unique pointer to the created factory
 */
std::unique_ptr<FigureFactory> InputTypeFactory::create_factory(const std::string& input) {
    static std::istringstream iss;
    static std::ifstream infile;
   
    if (input.find("random") != std::string::npos) {
        return std::make_unique<RandomFigureFactory>();
    }
    else if (input.find("stream") != std::string::npos) {
        iss.clear(); // clear state flags from previous use of stream
        iss.str(input.substr(input.find(' ') + 1));
        if (!iss.good())
            throw std::runtime_error("Broken stream");
        return std::make_unique<StreamFigureFactory>(iss);
    }
    else if (input.find("file") != std::string::npos) {
        infile.open(input.substr(input.find(' ') + 1));
        if (!infile.good())
            throw std::runtime_error("Broken file stream");
        return std::make_unique<StreamFigureFactory>(infile);
    }
    else 
        throw std::invalid_argument("Invalid string");
    return nullptr; // This should never be reached
}