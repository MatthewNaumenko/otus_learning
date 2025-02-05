#pragma once
#include <vector>

std::vector<char> readFromFile(const char *path);

void writeToFile(const char *path, const std::vector<char> &data);
