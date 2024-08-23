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
    std::cout<< std::bitset<64>(memory[i]) << "  => " <<memory[i] <<std::endl;
  }
}

void memCheck(char* StringNumber, uint64_t * memory){
     
}

int main (int argc, char *argv[]) {
  
  //working space
  uint64_t memory[10];
  //clear the working space
  for(int i =0; i < sizeof(memory) / 8; i++){
    memory[i] = 0;
  }

  //pretty useles considering argv exsits however...
  //used to stor intiger values of the  number 
  char* d10Word = new char[strlen(argv[1])];
  //string->int conversion
  for(int i =0; i < strlen(argv[1]); i++){
    d10Word[i] = argv[1][i] - 48;
  }
  
  //lenght of the number up to 2^64-1... for now  ofc
  uint64_t asizee = strlen(argv[1]);
  
  std::cout << '\n' << asizee;
  
  //current buffer being writen to 
  int bufIndex = 0;
  //exponent 
  int exp  = 0;
  printf("\n");
  for(int i = 0; i < (int)asizee/19+1; i++){
    int chunkSize = 19;
    if(i * 19 +19> asizee-1){
      chunkSize = asizee - i*19;
    }
    for(int j = 0  ; j < chunkSize; j++){
      memory[bufIndex] += betterPOW( exp) * d10Word[(asizee-1)-(i*19+j)];
      exp++;
    }
    //printf("ran cycle of  %d itterations", chunkSize);
    exp = 0;
    bufIndex ++;
  }

  printf("\n");
  showmem(memory, 10);
  
  //security check V2.0
  memCheck(argv[1], memory);
  return 0;
}



