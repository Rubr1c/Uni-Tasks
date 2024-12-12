#include <iostream>
#include <format>
#include <vector>

std::string coinScale(float c1, float c2, float c3) {
    if (c1 == c2) return std::format("Coin 3 is {}", c2 > c3 ? "Lighter" : "Heavier");
    if (c2 == c3) return std::format("Coin 1 is {}", c2 > c1 ? "Lighter" : "Heavier");
    if (c1 == c3) return std::format("Coin 2 is {}", c1 > c2 ? "Lighter" : "Heavier");

    throw std::runtime_error("fake not found");
}

