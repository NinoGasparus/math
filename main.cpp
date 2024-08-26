#include <bitset>
#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <cstdint>
#include <cmath>
#include "math.h"
void printNumber(uint64_t* number, int chunks){
  for(int i =chunks-1; i >=0; i--){
    std::cout << number[i];
  }


}

void printMem(uint64_t* mem, int size){
    for(int i =0; i < size; i++){
      std::cout << std::bitset<64>(mem[i]) << " => "  << mem[i] << '\n';
  }

}
int main(int argc, char* argv[]) {
  bigNumber* m = new bigNumber();
  m->sayHello();
  std::string number = ""; 

  char* arg = new char[3];
  arg[0] = '-';
  arg[1] = 'f';
  arg[2] = 'h';
  //production ready comparsion right there 
  if(argv[1][0]  == arg[0] && argv[1][1] == arg[1]){
    std::ifstream file(argv[2]);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    file >> number;
    file.close();
  }else{
    number = argv[2];
  }
  

    auto start = std::chrono::high_resolution_clock::now();
    int blockCount = std::floor(number.size() / 19) + 1;

    uint64_t* memory = new uint64_t[blockCount];
    std::memset(memory, 0, blockCount * sizeof(uint64_t));

    char* d10Word = new char[number.size()];
    for (size_t i = 0; i < number.size(); i++) {
        d10Word[i] = number[i] - '0';
    }

    // Length of the number
    uint64_t asizee = number.size();

    // Current buffer being written to
    int bufIndex = 0;
    // Exponent
    int exp = 0;

    for (int i = 0; i < (int)asizee / 19 + 1; i++) {
        int chunkSize = 19;
        if (i * 19 + 19 > asizee - 1) {
            chunkSize = asizee - i * 19;
        }
        for (int j = 0; j < chunkSize; j++) {
            memory[bufIndex] += betterPOW(exp) * d10Word[(asizee - 1) - (i * 19 + j)];
            exp++;
        }
        exp = 0;
        bufIndex++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    printMem(memory, blockCount);
  printf("\n");
    printNumber(memory, blockCount);
    delete[] memory;
    delete[] d10Word;

    return 0;
}

