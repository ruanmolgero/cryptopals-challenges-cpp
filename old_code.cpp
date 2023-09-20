#include <vector>
#include <iostream>
#include <unordered_map>

// old_challenge_s1.1
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

// old_challenge_s1.3

std::unordered_map<char, double> expected_frequency_texts = {
    {'e', 12.7},
    {'t', 9.1},
    {'a', 8.2},
    {'o', 7.5},
    {'i', 7.0},
    {'n', 6.7},
    {'s', 6.3},
    {'h', 6.1},
    {'r', 6.0},
    {'d', 4.3},
    {'l', 4.0},
    {'c', 2.8},
    {'u', 2.8},
    {'m', 2.4},
    {'w', 2.4},
    {'f', 2.2},
    {'g', 2.0},
    {'y', 2.0},
    {'p', 1.9},
    {'b', 1.5},
    {'v', 0.98},
    {'k', 0.77},
    {'j', 0.15},
    {'x', 0.15},
    {'q', 0.095},
    {'z', 0.074},
};

// std::unordered_map<char, double> expected_frequency_dictionaries = {
//     {'e', 11.16}, {'a', 8.50},
//     {'r', 7.58},  {'i', 7.54},
//     {'o', 7.16},  {'t', 6.95},
//     {'n', 6.65},  {'s', 5.74},
//     {'l', 5.49},  {'c', 4.54},
//     {'u', 3.63},  {'d', 3.38},
//     {'p', 3.17},  {'m', 3.01},
//     {'h', 3.00},  {'g', 2.47},
//     {'b', 2.07},  {'f', 1.82},
//     {'y', 1.78},  {'w', 1.29},
//     {'k', 1.10},  {'v', 1.01},
//     {'x', 0.29},  {'z', 0.27},
//     {'j', 0.2},   {'q', 0.2},
// };

std::unordered_map<char, int> calculateFrequency(const std::string &text)
{
    std::unordered_map<char, int> frequency;

    for (char c : text)
    {
        if (isalpha(c))
        {
            frequency[tolower(c)]++;
        }
    }

    return frequency;
}

std::string byteArrayToString(const std::vector<unsigned char> &byteArray)
{
    return std::string(byteArray.begin(), byteArray.end());
}

double textScore(const std::string &text)
{
    double score = 0;

    std::unordered_map<char, int> text_frequency = calculateFrequency(text);

    for (const auto &pair : text_frequency)
    {
        char letter = pair.first;
        int count = pair.second;
        if (expected_frequency_texts.count(letter) > 0)
        {
            double expected_percent = expected_frequency_texts[letter];
            double actual_percent = (static_cast<double>(count) / text.length()) * 100.0;
            // Usando a diferença absoluta tem-se um score que representa uma correlação inversa entre
            // as frequências do texto dado e esperadas
            score += std::abs(expected_percent - actual_percent);
        }
    }

    return score;
}

// std::string string_to_hex(const std::string &input)
// {
//     static const char hex_digits[] = "0123456789abcdef";

//     std::string output;

//     output.reserve(input.length() * 2);
//     for (unsigned char c : input)
//     {
//         output.push_back(hex_digits[c >> 4]);
//         output.push_back(hex_digits[c & 15]);
//     }

//     return output;
// }

std::string char_to_hex(char input)
{
    static const char hex_digits[] = "0123456789abcdef";

    std::string output;
    output.push_back(hex_digits[static_cast<unsigned char>(input) >> 4]);
    output.push_back(hex_digits[static_cast<unsigned char>(input) & 15]);

    return output;
}

int main()
{
    std::cout << "Hello, C++ on Linux!" << std::endl;

    // old_challenge_s1.3
    //  const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //  std::string hex_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    //  std::cout << std::hex << string_to_hex("x");
    //  for (char c : chars)
    //  {
    //      std::cout << "Character: " << c << " Score: " << textScore(byteArrayToString(repeatableXOR(hexToByteArray(hex_string), c))) << std::endl;
    //  }
    //  std::cout << byteArrayToString(repeatableXOR(hexToByteArray(hex_string), 'w')) << std::endl;

    return 0;
}