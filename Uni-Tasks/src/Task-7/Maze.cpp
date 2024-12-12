#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <format>

static std::ofstream output("../../../src/Task-7/maze_output.txt");

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
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); 
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

std::ostream& operator<<(std::ostream& stream, const std::vector<pos>& path) {
    stream << "[";
    for (const pos& p : path) {
        stream << std::format("({}, {})", p.first, p.second);
    }
    stream << "]";
    return stream;
}

std::vector<pos> dfs(pos start, pos goal) {
    save_maze();
    std::stack<pos> s;
    s.push(start);
    std::unordered_set<pos, PairHash> visited;
    std::unordered_map<pos, pos, PairHash> parents;
    parents[start] = { -1, -1 };

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

            for (int i = path.size() - 1; i >= 0; i--) {
                output << path[i].first << " " << path[i].second << (i == 0 ? "" : ", ");
            }

            std::reverse(path.begin(), path.end());
            output.close();
            return path;
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

    
    return {}; 
}
