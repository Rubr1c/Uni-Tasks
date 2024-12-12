#include <string>
#include <algorithm>
#include <vector>

bool areAnagramBySort(std::string word1, std::string word2) {
	if (word1.length() != word2.length()) return false;

	std::sort(word1.begin(), word1.end());
	std::sort(word2.begin(), word2.end());
	return word1 == word2;
}

bool areAnagramsByFrequency(const std::string& word1, const std::string& word2) {
	if (word1.length() != word2.length()) return false;

	std::vector<int> frequency(256, 0);

	for (int i = 0; i < word1.length(); i++) {
		frequency[word1[i]]++;
		frequency[word2[i]]--;
	}

	for (int& count : frequency) {
		if (count != 0) return false;
	}

	return true;
}