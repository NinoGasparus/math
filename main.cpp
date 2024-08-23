#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

void showmem(uint64_t* memory, int size){
  for(int i =0; i < size; i++){
    std::cout<< std::bitset<64>(memory[i]) << "  " <<std::endl;
  }
}
void increment(uint64_t* memory, int exp, char number, int bufIndex);

int main (int argc, char *argv[]) {
  
  uint64_t memory[10];
  for(int i =0; i < sizeof(memory) / 8; i++){
    memory[i] = 0;
  }

  showmem(memory, 10);

  char* d10Word = new char[strlen(argv[1])];

  for(int i =0; i < strlen(argv[1]); i++){
    d10Word[i] = argv[1][i] - 48;
  }

  for(int i =0; i < strlen(argv[1]); i++){
    printf("%d",d10Word[i]);
  }
  int asizee = strlen(argv[1]);
  printf("\n%d", asizee);
  int bufIndex = 0;
  int exp  =asizee-1;
  
  for(int i = 0  ; i < asizee ; i++){
    if(i%19  ==0 && i != 0){
      bufIndex++;
      exp = asizee-1;
    }
    increment(memory, exp, d10Word[i], bufIndex);
    exp--;

  }
  printf("\n");
  showmem(memory, 10);



  return 0;
}
void increment(uint64_t* memory, int exp, char number, int bufIndex){
  memory[bufIndex] += pow(10, exp) * number;

}
