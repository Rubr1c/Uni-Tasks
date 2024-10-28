#include "uni.h"

int main() {
	std::vector<std::string> colors = { "light", "dark","light", "dark", "light", "dark", "light", "dark"};
	int moves = partitionDisks(colors);

	for (int i = 0; i < colors.size(); i++) {
		std::cout << colors[i] << " ";
	}
	std::cout << "\nMoves: " << moves;
}



