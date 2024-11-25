#include "stream_figure_factory.hpp"

StreamFigureFactory::StreamFigureFactory(std::istream&& stream): is(stream) {}

std::unique_ptr<Figure> StreamFigureFactory::create_figure() {
    if (is.eof())
        throw std::ios_base::failure("End of file reached");
    std::string buff;
    std::getline(is, buff);
    StringToFigureConverter creator;
    std::unique_ptr<Figure> fig = nullptr;
    try {
        fig = creator.make_figure(buff);
    } catch (std::exception &e) {
        throw std::invalid_argument("Stream contains invalid lines");
    }
    return fig;
}