#include <iostream>
#include <vector>
#include <algorithm>


int sortDisks(std::vector<std::string>& colors) {
	static int moveCount = 0;
	std::sort(colors.begin(), colors.end(), 
		[](const std::string& a,const std::string& b) {
			if (a == "light" && b != "light") {
				moveCount++;
				return true;
			}
			return false;
		});

	return moveCount;
}

int partitionDisks(std::vector<std::string>& colors) {
	static int moveCount = 0;
	std::partition(colors.begin(), colors.end(), 
		[](const std::string& color) {
			if (color == "light") {
				moveCount++;
				return true;
			}
			return false;
		});
	return moveCount;
}