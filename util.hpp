// util.h
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

// challenge 1.1
std::string hex_to_binary_c11(const std::string &hex);
std::string bin_to_base64(const std::string &bin);
// challenge 1.2
std::vector<uint8_t> hex_to_byte_array(const std::string &hex);
std::string byteArrayToBase64(const std::vector<uint8_t> &bytearray);
std::vector<u_int8_t> fixedXOR(const std::vector<uint8_t> &hex1, const std::vector<uint8_t> &hex2);
// challenge 1.3
struct Candidate
{
    std::string decoded_string;
    char xor_char;
};
std::string hex_to_binary(const std::string &hex);
std::string xor_single_char(const std::string &string, int i);
std::vector<Candidate> findCandidates(const std::string &string);

#endif
