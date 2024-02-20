//
// Created by Doge on 20/02/2024.
//

#ifndef OBFUSCATIONTEST_BASE64_H
#define OBFUSCATIONTEST_BASE64_H

#include <string>

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string base64_encode(const std::string& s);
std::string base64_decode(std::string const& encoded_string);

#endif //OBFUSCATIONTEST_BASE64_H
