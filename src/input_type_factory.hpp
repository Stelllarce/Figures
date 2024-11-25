#pragma once
#include "stream_figure_factory.hpp"
#include "random_figure_factory.hpp"
#include "abstract_factory.hpp"

class InputTypeFactory : public AbstractFactory {
public:
    std::unique_ptr<FigureFactory> create(const std::string& in_type, std::istream* stream = nullptr) override;
};