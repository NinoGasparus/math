#include "bigNumber.h"
#include <csignal>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <sys/types.h>

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

uint64_t getDiff(uint64_t n1, uint64_t n2){
  if(n1 > n2){
    return n1;
  }else{
    return n2;
  }
}
void bigAdd(bigNumber n1, bigNumber n2,  bigNumber dest){
  uint64_t* n1mem =  n1.memory;
  uint64_t* n2mem =  n2.memory;
  uint64_t* n3mem =  dest.memory;
  
  uint64_t diff =  0;

  bool carry = false;
  int bufIndex = 0;
  while(true){
    n3mem[bufIndex] = n1mem[bufIndex] +  n2mem[bufIndex];
    //resoult of addition can never be smaller than any of operands, one check is enough however... checking both doesnt  hurt performance either
    if(n3mem[bufIndex] < n1mem[bufIndex] || n3mem[bufIndex] < n2mem[bufIndex]){
      //overflow
      carry = true;
      //yes
      diff = getDiff(n1mem[bufIndex] , n2mem[bufIndex]);
      n3mem[bufIndex] =  diff;
    }
  }  
}



