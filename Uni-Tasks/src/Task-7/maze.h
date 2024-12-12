#pragma once

typedef std::pair<int, int> pos;

std::vector<pos> dfs(pos start, pos goal);
std::ostream& operator<<(std::ostream& stream, const std::vector<pos>& path);