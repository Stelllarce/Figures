#pragma once
#include <string>

class StringConverter {
public:
    virtual std::string to_str() const = 0;
    virtual ~StringConverter() = default;
};