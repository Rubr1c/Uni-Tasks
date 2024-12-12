#include "textwrapping.h"

std::vector<std::string> TextWrapper::wrappedText;

void TextWrapper::WrapText(const std::string& text, int lineWidth) {
    std::vector<std::string> words;
    size_t start = 0, end;

    while ((end = text.find(" ", start)) != std::string::npos) {
        words.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    words.push_back(text.substr(start));


    int n = words.size();

    std::vector<std::vector<int>> fitTable(n);
    for (int i = 0; i < n; ++i) {
        int currentWidth = 0;
        for (int j = i; j < n; ++j) {
            if (currentWidth + words[j].length() + (j > i ? 1 : 0) <= lineWidth) {
                fitTable[i].push_back(j);
                currentWidth += words[j].length() + (j > i ? 1 : 0);
            }
            else {
                break;
            }
        }
    }

    std::vector<int> minCost(n + 1, INT_MAX);
    std::vector<int> wordBreaks(n + 1);
    minCost[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            auto it = std::find(fitTable[j].begin(), fitTable[j].end(), i - 1);
            if (it != fitTable[j].end()) {
                int lineCost = calculateLineCost(words, j, i - 1, lineWidth);
                if (minCost[j] != INT_MAX && minCost[j] + lineCost < minCost[i]) {
                    minCost[i] = minCost[j] + lineCost;
                    wordBreaks[i] = j;
                }
            }
        }
    }

    wrappedText = reconstructLines(words, wordBreaks, n);
}


std::string TextWrapper::Build() {
    std::stringstream ss;
    for (const std::string& line : wrappedText) {
        ss << line << "\n";
    }
    return ss.str();
}

void TextWrapper::Clear() {
    wrappedText.clear();
}

int TextWrapper::calculateLineCost(const std::vector<std::string>& words, int start, int end, int lineWidth) {
    int totalLength = 0;
    for (int i = start; i <= end; ++i) {
        totalLength += words[i].length() + (i > start ? 1 : 0);
    }

    int gap = lineWidth - totalLength;
    return gap * gap;
}

std::vector<std::string> TextWrapper::reconstructLines(const std::vector<std::string>& words,
    const std::vector<int>& wordBreaks,
    int n) {
    std::vector<std::string> lines;
    int end = n;

    while (end > 0) {
        int start = wordBreaks[end];
        std::string line;
        for (int i = start; i < end; ++i) {
            line += (line.empty() ? "" : " ") + words[i];
        }
        lines.insert(lines.begin(), line);
        end = start;
    }

    return lines;
}

