#include "util.hpp"

int main()
{
    std::string str1 = "1c0111001f010100061a024b53535009181c";
    std::vector<uint8_t> hex1 = hex_to_byte_array(str1);
    std::string str2 = "686974207468652062756c6c277320657965";
    std::vector<uint8_t> hex2 = hex_to_byte_array(str2);
    std::vector<uint8_t> xor_h1_h2 = fixedXOR(hex1, hex2);
    for (uint8_t byte : xor_h1_h2)
    {
        std::cout << std::hex << static_cast<int>(byte);
    }
    std::cout << std::endl;

    return 0;
}