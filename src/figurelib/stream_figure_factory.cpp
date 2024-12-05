#include "stream_figure_factory.hpp"

/**
 * @brief Construct a new StreamFigureFactory::StreamFigureFactory object
 * @param stream The stream to read from
 */
StreamFigureFactory::StreamFigureFactory(std::unique_ptr<std::istream> stream): is(std::move(stream)) {}

/**
 * @brief Create a figure from the stream. Can be invoked as long as the stream is not empty
 * @return std::unique_ptr<Figure> A unique pointer to the created figure
 */
std::unique_ptr<Figure> StreamFigureFactory::create_figure() {
    if (is->eof()) // Stream is empty
        throw std::ios_base::failure("End of file reached");
    std::string buff;
    std::getline(*is, buff);
    StringToFigureConverter creator;
    std::unique_ptr<Figure> fig = nullptr;
    try {
        fig = creator.create_figure(buff);
    } catch (std::exception &e) {
        throw std::invalid_argument("Stream contains invalid lines");
    }
    return fig;
}