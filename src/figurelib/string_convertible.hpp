#pragma once
#include <string>
#include <cmath> // for std::floor

/**
 * @brief Interface for converting objects to strings
 */
class StringConvertible {
public:
    virtual std::string to_str() const = 0;
    virtual ~StringConvertible() = default;
protected:
    /**
     * @brief Convert a double to a string (helper function for derived classes)
     */
    static std::string stringify(double a) {
        std::string str = std::to_string(a);
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        str.erase(str.find_last_not_of('.') + 1, std::string::npos);
        return str;
    }
};