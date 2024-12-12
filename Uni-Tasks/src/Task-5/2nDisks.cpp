#include <iostream>  
#include <vector>  
#include <algorithm>

std::ostream& operator<<(std::ostream& stream, 
    const std::vector<std::string>& vec) {
    stream << "{";
    for (int i = 0; i < vec.size(); i++) {
        stream << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    stream << "}";
    return stream;
}

int sort2nDisks(int n) {  
   std::vector<std::string> disks(n * 2);

   int i = 0;
   std::generate(disks.begin(), disks.end(), [&i]() {
       return (i++ % 2 == 0 ? "dark" : "light");
       });

   int moves = 0;
   std::cout << "Starting Array: " << disks << "\n\n";
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n * 2 - 1; j++) {
           if (disks[j] == "dark" && disks[j + 1] == "light") {
               std::swap(disks[j], disks[j + 1]);
               std::cout << "Swaped Index: " << j << " and " << j + 1;
               std::cout << "\nCurrent Array: " << disks << "\n\n";
               moves++;
           }
       }
   }

   return moves;
}