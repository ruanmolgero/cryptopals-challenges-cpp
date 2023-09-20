#include "util.hpp"

std::string hex_to_binary_c11(const std::string &hex)
{
    std::unordered_map<char, std::string> hexToBinMap{
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'a', "1010"},
        {'b', "1011"},
        {'c', "1100"},
        {'d', "1101"},
        {'e', "1110"},
        {'f', "1111"},
    };

    std::string binary;
    for (char c : hex)
    {
        if (hexToBinMap.find(tolower(c)) != hexToBinMap.end())
        {
            binary += hexToBinMap[tolower(c)];
        }
        else
        {
            // Assumindo que a entrada será apenas hexadecimal
        }
    }

    return binary;
}

std::string bin_to_base64(const std::string &bin)
{
    // Vetor de caracteres usado para dar achar caractere base64 correspondente
    // após transformar de binary para sexteto
    const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64;
    int index = 0;
    int bitsRemaining = 0;

    for (char c : bin)
    {
        // Conversão string para int
        int bit = c - '0';

        // Append bit ao valor de index
        index = (index << 1) | bit;
        bitsRemaining++;

        // Ao completar 6 bits temos 1 valor equivalente em base64
        if (bitsRemaining == 6)
        {
            base64 += base64Chars[index];
            index = 0;
            bitsRemaining = 0;
        }
    }

    // Caso a quantidade de bits não seja multipla de 6 completamos o sexteto
    // e adicionamos o padding
    if (bitsRemaining > 0)
    {
        // Shift left a qtd de vezes necessárias pra completar um sexteto
        index = index << (6 - bitsRemaining);
        base64 += base64Chars[index];
        // Adição do padding
        while (bitsRemaining < 6)
        {
            base64 += '=';
            bitsRemaining++;
        }
    }

    return base64;
}

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