#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>

std::ofstream output("../../../src/Maze/maze_output.txt");

static constexpr bool maze[15][15] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


struct PairHash {
	size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

typedef std::pair<int, int> pos;

void save_maze() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			output << std::to_string(maze[i][j]) << " ";
		}
		output << "\n";
	}
}

void dfs(pos start, pos goal) {
	save_maze();
	std::stack<pos> s;
	s.push(start);
	std::unordered_set<pos, PairHash> visited;
	std::unordered_map<pos, pos, PairHash> parents;
	parents[start] = {-1, -1};

	constexpr pos moves[4] = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1}
	};

	while (!s.empty()) {
		pos current = s.top();
		s.pop();

		visited.insert(current);

		if (current == goal) {
			std::vector<pos> path;
			path.reserve(parents.size());

			while (current.first != -1) {
				path.push_back(current);
				current = parents[current];
			}
			output << "Path: \n";
			for (int i = path.size() - 1; i >= 0; i--) {
				std::cout << "(" << path[i].first << "," << path[i].second << ")";
				output << path[i].first << " " << path[i].second << (i == 0 ? "" : ", ");
			}
			std::cout << std::endl;
			return;
		}

		for (auto& move : moves) {
			pos neighbour = { (current.first + move.first), (current.second + move.second) };
			if ((neighbour.first >= 0 && neighbour.first < 15) &&
				(neighbour.second >= 0 && neighbour.second < 15) &&
				maze[neighbour.first][neighbour.second] == 1 &&
				!visited.contains(neighbour)) {

				s.push(neighbour);
				parents[neighbour] = current;
			}
		}
		
	}
	output.close();
}