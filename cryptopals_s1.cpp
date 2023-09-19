#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Tradução de entradas hex para binário usando hash
std::string hexToBinary(const std::string &hex)
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

std::string binToBase64(const std::string &bin)
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

std::vector<uint8_t> hexToByteArray(const std::string &hex)
{
    std::vector<uint8_t> byteArray;

    // Garantir que a string tem tamanho par
    if (hex.length() % 2 != 0)
    {
        std::cerr << "Erro: A string hex deve ter uma quantidade par de caracteres";
        return byteArray;
    }

    // Percorre hex em pares para obter 1 byte
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        std::string byteString = hex.substr(i, 2);
        try
        {
            uint8_t byte = std::stoul(byteString, nullptr, 16);
            byteArray.push_back(byte);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Invalid hex character found: " << byteString << std::endl;
            break;
        }
    }

    return byteArray;
}

std::string byteArrayToBase64(const std::vector<uint8_t> &bytearray)
{
    // Vetor de caracteres usado para dar achar caractere base64 correspondente
    // após transformar de binary para sexteto
    const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64;

    // Percorre bytearray pegando 3 bytes (24 bits ou 4 caracteres base64)
    for (size_t i = 0; i < bytearray.size(); i += 3)
    {

        // Trata 3 bytes por vez
        uint32_t chunk = 0;
        for (int j = 0; j < 3; j++)
        {
            // Aloca espaço no chunk e garantido que nao estouramos o tamanho do bytearray
            chunk <<= 8;
            if (i + j < bytearray.size())
            {
                chunk |= bytearray[i + j];
            }
        }

        // Itera 3 vezes (0, 1, 2) visto que cada chunk possui 3 bytes apenas
        for (int j = 0; j < 3; ++j)
        {
            // Garante que não estouramos o bytearray
            if (i * 4 / 3 + j < bytearray.size() * 4 / 3)
            {
                // Isola 1 byte (right shift) e usa a mascara 0x3f ('00111111') para pegar o valor do index
                uint8_t index = (chunk >> (18 - j * 6)) & 0x3f;
                base64 += base64Chars[index];
            }
            // se estouramos adicionamos o padding necessário
            else
            {
                base64 += '=';
            }
        }
    }

    return base64;
}

int main()
{
    std::string hex_value = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::vector<u_int8_t> bytearray_value = hexToByteArray(hex_value);
    std::string base64_value = byteArrayToBase64(bytearray_value);
    std::cout << base64_value << std::endl;
    // std::cout << "Hello, C++ on Linux!" << std::endl;
    return 0;
}