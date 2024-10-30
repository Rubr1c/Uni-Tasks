#include <iostream>
#include <unordered_map>
#include <algorithm>

bool areAnagramBySort(std::string word1, std::string word2) {
	if (word1.length() != word2.length()) return false;

	std::sort(word1.begin(), word1.end());
	std::sort(word2.begin(), word2.end());
	return word1 == word2;
}

bool areAnagramByMap(const std::string& word1, const std::string& word2) {
	if (word1.length() != word2.length()) return false;

	std::unordered_map<char, std::pair<int, int>> count;

	for (int i = 0; i < word1.length(); i++) {
		count[word1[i]].first++;
		count[word2[i]].second++;
	}

	for (const auto& entry : count) {
		if (entry.second.first != entry.second.second) 
			return false;
		
	}
	return true;
}

bool areAnagramsBySum(const std::string& word1, const std::string& word2) {
	if (word1.length() != word2.length()) return false;

	int sum = 0;

	for (int i = 0; i < word1.length(); i++) {
		sum += word1[i];
		sum -= word2[i];
	}

	return sum == 0;
}