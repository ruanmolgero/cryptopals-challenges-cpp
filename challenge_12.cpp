#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<uint8_t> hex_to_byte_array(const std::string &hex)
{
    std::vector<uint8_t> byte_array;

    // Garantir que a string tem tamanho par
    if (hex.length() % 2 != 0)
    {
        std::cerr << "Erro: A string hex deve ter uma quantidade par de caracteres";
        return byte_array;
    }

    // Percorre hex em pares para obter 1 byte
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        std::string byteString = hex.substr(i, 2);
        try
        {
            uint8_t byte = std::stoul(byteString, nullptr, 16);
            byte_array.push_back(byte);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Invalid hex character found: " << byteString << std::endl;
            break;
        }
    }

    return byte_array;
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

std::vector<u_int8_t> fixedXOR(const std::vector<uint8_t> &hex1, const std::vector<uint8_t> &hex2)
{
    std::vector<uint8_t> xor_array(hex1.size());
    if (hex1.size() != hex2.size())
    {
        std::cerr << "Erro: Ambas entradas devem ter o mesmo tamanho";
        return xor_array;
    }

    for (size_t i = 0; i < hex1.size(); i++)
    {
        xor_array[i] = hex1[i] ^ hex2[i];
    }

    return xor_array;
}

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