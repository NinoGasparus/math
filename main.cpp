#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

uint64_t betterPOW(int exp){
  uint64_t base = 1;
  for(int  i =  0; i < exp; i++){
    base *= 10;
  }
  return base;
}
void showmem(uint64_t* memory, int size){
  for(int i =0; i < size; i++){
    std::cout<< std::bitset<64>(memory[i]) << "  " <<std::endl;
  }
}

int main (int argc, char *argv[]) {
  
  uint64_t memory[10];
  for(int i =0; i < sizeof(memory) / 8; i++){
    memory[i] = 0;
  }

 // showmem(memory, 10);

  char* d10Word = new char[strlen(argv[1])];

  for(int i =0; i < strlen(argv[1]); i++){
    d10Word[i] = argv[1][i] - 48;
  }

  int asizee = strlen(argv[1]);
  printf("\n%d", asizee);
  int bufIndex = 0;
  int exp  =  asizee-1;
  printf("\n");
  
  for(int i = 0  ; i < asizee ; i++){
    memory[bufIndex] += betterPOW( exp) * d10Word[i];
    exp--;

  }
    printf("\n");
  showmem(memory, 10);
  

  //uint64_t temp = 18446744073709551615UL;
  //showmem(&temp, 1);
  uint64_t argValue = std::strtoull(argv[1], nullptr, 10);
  if (memory[0] == argValue) {
        std::cout << "Passed" << std::endl;
    } else {
        std::cout << "Failed" << std::endl;
    }
  return 0;
}
