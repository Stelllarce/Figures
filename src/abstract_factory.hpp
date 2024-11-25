#pragma once
#include <memory>
#include "figure_factory.hpp"

class AbstractFactory {
public:
    virtual std::unique_ptr<FigureFactory> create(const std::string& in_type, std::istream* stream = nullptr) = 0;
    ~AbstractFactory() = default;
};  