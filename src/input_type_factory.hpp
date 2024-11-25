#pragma once
#include "stream_figure_factory.hpp"
#include "random_figure_factory.hpp"

class InputTypeFactory {
    FigureFactory* create_factory(const std::string& in_type, std::istream* stream = nullptr) noexcept;
};