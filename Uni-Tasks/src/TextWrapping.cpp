#include <iostream>
#include <string>
#include <map>

void wrapText(const std::string& text) {
	std::map<int, std::string> map;


	std::string str = "";
	for (const char& ch : text) {
		if (ch == ' ') {
			map[str.length()] = str;
			str = "";
			continue;
		}
		str += ch;
	}


	for (auto& entry : map) {
		std::cout << entry.first << " : " << entry.second << ", ";
	}
}