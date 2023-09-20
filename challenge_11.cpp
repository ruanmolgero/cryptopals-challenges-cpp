#include "util.hpp"

int main()
{
    // set1:
    // challenge 1
    std::string hex_value = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string binary_value = hex_to_binary_c11(hex_value);
    std::cout << binary_value << std::endl;
    std::string base64_value = bin_to_base64(binary_value);
    std::cout << base64_value << std::endl;
    return 0;
}