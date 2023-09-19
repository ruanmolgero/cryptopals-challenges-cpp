#include "util.hpp"

#include <string>
#include <iostream>

std::string hex_to_binary(const std::string &hex)
{
    std::string binary;
    for (size_t j = 0; j < hex.length(); j += 2)
    {
        std::string hexByte = hex.substr(j, 2);
        char chr = static_cast<char>(std::stoi(hexByte, nullptr, 16));
        binary.push_back(chr);
    }
    return binary;
}

int main()
{
    return 0;
}