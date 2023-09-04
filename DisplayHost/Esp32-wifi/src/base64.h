#pragma once

#include <string>
#include <vector>

std::string base64encode(const std::vector<uint8_t> &bytes);

std::vector<uint8_t> base64decode(const char* encoded_string);