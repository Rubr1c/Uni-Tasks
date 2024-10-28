#pragma once

#include <iostream>
#include <vector>

#include "CoinScale.h"

int TowerOfHanoi(int n, char source, char auxiliary, char destination);

bool areAnagramByMap(const std::string& word1, const std::string& word2);

int sortDisks(std::vector<std::string>& colors);
int partitionDisks(std::vector<std::string>& colors);





