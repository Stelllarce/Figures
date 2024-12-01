#pragma once
#include <memory>
#include "figure_factory.hpp"

/**
 * @brief Abstract factory interface
 */
class AbstractFactory {
public:
    /**
     * @brief Create a figure factory
     * @param in_type The type of the factory
     * @param stream Pointer to stream, if any
     * @return A unique pointer to the created factory
     */
    virtual std::unique_ptr<FigureFactory> create(const std::string& in_type, std::istream* stream = nullptr) = 0;
    ~AbstractFactory() = default;
};  