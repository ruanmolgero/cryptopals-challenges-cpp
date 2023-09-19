#include "util.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

struct Candidate {
    std::string decoded_string;
    char xor_char;
};

// std::string hex_to_binary(const std::string &hex)
// {
//     std::string binary;
//     for (size_t j = 0; j < hex.length(); j += 2)
//     {
//         std::string hexByte = hex.substr(j, 2);
//         char chr = static_cast<char>(std::stoi(hexByte, nullptr, 16));
//         binary.push_back(chr);
//     }
//     return binary;
// }

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
    int threshold = 10;
    // Continua até achar apenas 1 candidato
    while (true)
    {
        candidates.clear();

        for (int i = 65; i <= 122; i++)
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

        if (candidates.size() == 1)
        {
            break;
        }
    }

    return candidates;
}

int main()
{
    std::string xored_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::vector<Candidate> finalCandidates = findCandidates(xored_string);

    if (!finalCandidates.empty())
    {
        std::cout << "Final Candidate: " << finalCandidates[0].decoded_string << std::endl;
        std::cout << "Character used to XOR: " << finalCandidates[0].xor_char << std::endl;
    }
    else
    {
        std::cout << "No candidates found." << std::endl;
    }

    return 0;
}