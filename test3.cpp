#include <chrono>
#include <iostream>
#include <cstdint>
#include <bitset>

extern "C" bool smartAdd(uint64_t num1, uint64_t num2, uint64_t* dest);

int main() {
    uint64_t x  = 0;
    uint64_t y  = 10;
    uint64_t z  = 0;
    uint64_t q = 0;
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;  
 start = std::chrono::high_resolution_clock::now();
    //q = smartAdd(x,y,&z);
  z = x+y;
 end= std::chrono::high_resolution_clock::now();
std::cout << "took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << std::endl;
   // std::cout << " flags: " << smartAdd(x,y,&z) << std::endl;
    std::cout << "z =  " << z << std::endl;
    std::cout << "q =  " << std::bitset<64>(q) << std::endl;
    return 0;
}
