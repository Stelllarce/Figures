#pragma once
#include "stream_figure_factory.hpp"
#include "random_figure_factory.hpp"
#include "abstract_factory.hpp"

/**
 * @brief Factory class for creating factories based on input type
 */
class InputTypeFactory : public AbstractFactory {
public:
    std::unique_ptr<FigureFactory> create_factory(const std::string& input) override;
};