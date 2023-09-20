#include "util.hpp"

// challenge 1.1
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

// challenge 1.2
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

// challenge 1.3

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

std::string xor_single_char(const std::string &string, int i)
{
    std::string binary = hex_to_binary(string);
    std::string result;

    for (char b : binary)
    {
        result.push_back(b ^ i);
    }

    return result;
}

std::vector<Candidate> findCandidates(const std::string &string)
{
    // Vetor para guardar candidatos potenciais
    // std::vector<std::string> candidates;
    std::vector<Candidate> candidates;

    // Threshold para avaliar candidatos
    int threshold = 0;
    // Continua até achar apenas 1 candidato
    while (true)
    {
        candidates.clear();

        for (int i = 0; i <= 255; i++)
        {
            // std::string evaluated = xor_thekey(i);
            std::string evaluated = xor_single_char(string, i);
            int count = 0;

            // Conta ocorrências de determinados caracteres (ETAOIN SHRDLU)
            // Tentou-se fazer usando tabela de frequências mas os resultados foram ruins
            for (char c : evaluated)
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

            // Checa pra ver se bateu threshold e se existem caracteres de controle
            if (evaluated.find_first_of("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F") == std::string::npos && count > threshold)
            {
                Candidate candidate;
                candidate.decoded_string = evaluated;
                candidate.xor_char = static_cast<char>(i);
                candidates.push_back(candidate); // Add potential candidate.
            }
        }

        threshold++;

        if (candidates.size() == 1 || threshold > 40)
        {
            break;
        }
    }

    return candidates;
}