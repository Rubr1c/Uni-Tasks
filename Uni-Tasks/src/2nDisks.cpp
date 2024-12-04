#include <iostream>  
#include <vector>  
#include <algorithm>  

int sort2nDisks(int n) {  
   std::vector<std::string> disks;
   disks.reserve(n * 2);
   for (int i = 0; i < n; i++) {  
       disks.push_back("dark");  
       disks.push_back("light");  
   }

   int moves = 0;

   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n * 2 - 1; j++) {
           if (disks[j] == "dark" && disks[j + 1] == "light") {
               std::swap(disks[j], disks[j + 1]);
               moves++;
           }
       }
   }

   return moves;
}