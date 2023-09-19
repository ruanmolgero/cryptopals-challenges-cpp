#include <iostream>
#include <vector>
#include <unordered_map>

// se1
// challenge 1
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

std::vector<uint8_t> hexToByteArray(const std::string &hex)
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

// challenge 2
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

// challenge 3

std::string xor_single_char(const std::string &string, int i)
{
    std::string binary = hexToBinary(string);
    std::string result;

    for (char b : binary)
    {
        result.push_back(b ^ i);
    }

    return result;
}

// bool evaluate(std::string &plain_string, int i)
// {
//     bool potencial_candidate = false;
//     std::string xored_string = xor_single_char(plain_string, i);

//     int count;
//     for (char c : plain_string)
//     {
//         if (std::tolower(c) == 'e' || std::tolower(c) == 't' || std::tolower(c) == 'a' ||
//             std::tolower(c) == 'o' || std::tolower(c) == 'i' || std::tolower(c) == 'n' ||
//             std::tolower(c) == ' ' || std::tolower(c) == 's' || std::tolower(c) == 'h' ||
//             std::tolower(c) == 'r' || std::tolower(c) == 'd' || std::tolower(c) == 'l' ||
//             std::tolower(c) == 'u')
//         {
//             count++;
//         }

//         if (xored_string.find_first_of("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F") == std::string::npos && count > xored_string.size() / 2)
//         {
//             potencial_candidate = true;
//             // std::cout << "Potential match at " << i << " with " << xored_string << std::endl;
//         }
//     }

//     return potencial_candidate;
// }

int main()
{
    // std::cout << "Hello, C++ on Linux!" << std::endl;

    // set1:
    // challenge 1
    // std::string hex_value = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    // std::vector<u_int8_t> bytearray_value = hexToByteArray(hex_value);
    // std::string base64_value = byteArrayToBase64(bytearray_value);
    // std::cout << base64_value << std::endl;

    // challenge 2
    // std::string str1 = "1c0111001f010100061a024b53535009181c";
    // std::vector<uint8_t> hex1 = hexToByteArray(str1);
    // std::string str2 = "686974207468652062756c6c277320657965";
    // std::vector<uint8_t> hex2 = hexToByteArray(str2);
    // std::vector<uint8_t> xor_h1_h2 = fixedXOR(hex1, hex2);
    // for (uint8_t byte : xor_h1_h2)
    // {
    //     std::cout << std::hex << static_cast<int>(byte);
    // }
    // std::cout << std::endl;

    // challenge 3
    std::string xored_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    std::vector<std::string> candidates;
    int threshold = 10;
    while (candidates.size() != 1)
    {
        candidates.clear();
        for (int i = 65; i <= 122; i++)
        {
            std::string unxored = xor_single_char(xored_string, i);
            int count = 0;

            for (char c : unxored)
            {
                char lc = std::tolower(c);
                if (lc == 'e' || lc == 't' || lc == 'a' ||
                    lc == 'o' || lc == 'i' || lc == 'n' ||
                    lc == ' ' || lc == 's' || lc == 'h' ||
                    lc == 'r' || lc == 'd' || lc == 'l' ||
                    lc == 'u')
                {
                    count++;
                }
            }

            if (unxored.find_first_of("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F") == std::string::npos && count > threshold)
            {
                candidates.push_back(unxored);
            }
        }
        threshold++;
    }

    if (!candidates.empty())
    {
        // Print the final candidate.
        std::cout << "Final Candidate: " << candidates[0] << std::endl;
    }
    else
    {
        std::cout << "No candidates found." << std::endl;
    }

    return 0;
}