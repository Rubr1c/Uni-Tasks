#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <iomanip>
#include <sstream>

class TextWrapper {
public:
	static void WrapText(const std::string& text, int lineWidth);
	static std::string Build();
	static void Clear();
private:
	static std::vector<std::string> wrappedText;
	static int calculateLineCost(const std::vector<std::string>& words, 
								 int start, int end, int lineWidth);

	static std::vector<std::string> reconstructLines(const std::vector<std::string>& words,
		const std::vector<int>& wordBreaks,
		int n);
};
