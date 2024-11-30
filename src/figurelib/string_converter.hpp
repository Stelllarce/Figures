#pragma once
#include <string>
#include <cmath> // for std::floor

class StringConverter {
public:
    virtual std::string to_str() const = 0;
    virtual ~StringConverter() = default;
protected:
    static std::string stringify(double a) {
        std::string str = std::to_string(a);
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        str.erase(str.find_last_not_of('.') + 1, std::string::npos);
        return str;
    }
};