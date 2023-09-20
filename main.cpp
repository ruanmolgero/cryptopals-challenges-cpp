#include "util.hpp"

int main()
{
    std::cout << std::endl;
    std::cout << "Pré-desafio LabSec por Ruan Luiz Molgero Lopes" << std::endl
              << std::endl;
    std::cout << "Desafio 1.1:" << std::endl
              << std::endl;

    std::string hex_value = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string binary_value = hex_to_binary_c11(hex_value);
    std::string base64_value = bin_to_base64(binary_value);

    std::cout << "Valor em hex: " << std::hex << hex_value << std::endl;
    std::cout << "Valor em binário: " << binary_value << std::endl;
    std::cout << "Valor final em base64: " << base64_value << std::endl
              << std::endl;

    std::cout << "Desafio 1.2:" << std::endl
              << std::endl;

    std::string str1 = "1c0111001f010100061a024b53535009181c";
    std::string str2 = "686974207468652062756c6c277320657965";
    std::vector<uint8_t> hex1 = hex_to_byte_array(str1);
    std::vector<uint8_t> hex2 = hex_to_byte_array(str2);
    std::vector<uint8_t> xor_h1_h2 = fixedXOR(hex1, hex2);

    std::cout << "Valor string1: " << std::hex << str1 << std::endl;
    std::cout << "Valor string2: " << std::hex << str2 << std::endl;

    std::cout << "Valor final: ";
    for (uint8_t byte : xor_h1_h2)
    {
        std::cout << std::hex << static_cast<int>(byte);
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Desafio 1.3:" << std::endl
              << std::endl;

    std::string xored_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::vector<Candidate> finalCandidates = findCandidates(xored_string);

    std::cout << "Valor XOR'd string : " << std::hex << xored_string << std::endl;
    std::cout << "Após decriptar a string usando todos os caracteres do alfabeto como máscara encontrou-se que: " << std::endl;

    if (!finalCandidates.empty())
    {
        std::cout << "\tCaractere usado para máscara: " << finalCandidates[0].xor_char << std::endl;
        std::cout << "\tFrase encontrada: " << finalCandidates[0].decoded_string << std::endl;
    }
    else
    {
        std::cout << "No candidates found." << std::endl;
    }

    return 0;
}