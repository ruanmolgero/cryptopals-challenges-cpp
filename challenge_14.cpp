#include "util.hpp"

int main()
{
    std::ifstream inputFile("challenge_14.txt");

    // Checa se abriu corretamente
    if (!inputFile.is_open())
    {
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        return 1;
    }

    for (int i = 0; i < 60; i++)
    {
        std::string line;
        if (std::getline(inputFile, line))
        {
            // Lê joga no display a linha atual
            std::cout << "Line " << i + 1 << ": " << line << std::endl;
        }
        else
        {
            // Tratador caso não haja mais linhas para ler
            std::cerr << "Arquivo chegou ao fim." << std::endl;
            break;
        }

        std::vector<Candidate> finalCandidates = findCandidates(line);

        if (!finalCandidates.empty())
        {
            std::cout << "Line " << i + 1 << ": " << line << std::endl;
            std::cout << "Final Candidate: " << finalCandidates[0].decoded_string << std::endl;
            std::cout << "Character used to XOR: " << finalCandidates[0].xor_char << std::endl;
        }
        else
        {
            std::cout << "No candidates found." << std::endl;
        }
    }

    return 0;
}