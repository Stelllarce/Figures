#pragma once
#include <string>
#include <cmath> // for std::floor

class StringConverter {
public:
    virtual std::string to_str() const = 0;
    virtual ~StringConverter() = default;
protected:
    static std::string stringify(double a) {
        if (a - std::floor(a) < 0.1)
            return std::to_string(static_cast<int>(a));
        else
            return std::to_string(a);
    }
};