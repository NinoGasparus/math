#include "bigNumber.h"
#include <iostream>
#include <bitset>

void bigPrint(bigNumber number){
  
  for(int i = number.blockCount-1; i >=0; i--){
    std::cout << number.memory[i];
  }
}



void printMem(int id, bigNumber number){
  if(id == -1){
    for(int i =0; i < number.blockCount; i++){
      std::cout << std::bitset<64>(number.memory[i]) << " => "  << number.memory[i] << '\n';
    }
  }else{
      std::cout << std::bitset<64>(number.memory[id]) << " => "  << number.memory[id] << '\n';
  }
}

void printMem(bigNumber number){
 printMem(-1, number);
}




