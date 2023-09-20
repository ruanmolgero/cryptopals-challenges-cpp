#include "util.hpp"

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