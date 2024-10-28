#include <iostream>

int TowerOfHanoi(int n, char source, char auxiliary, char destination) {
    static int moveCount = 0;
    if (n == 0) return moveCount;

    TowerOfHanoi(n - 1, source, auxiliary, destination);

    std::cout << "Move disk " << n << " from " << source << " to " << auxiliary << std::endl;
    moveCount++;

    TowerOfHanoi(n - 1, destination, auxiliary, source);

    std::cout << "Move disk " << n << " from " << auxiliary << " to " << destination << std::endl;
    moveCount++;

    TowerOfHanoi(n - 1, source, auxiliary, destination);
}
