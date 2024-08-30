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


uint64_t getOverflow(uint64_t n1, uint64_t n2){
  // ||         ONLY WORKS IF THERE IS OVERFLOW ELSE GIVES INCORRECT RESOULTS
  //limit is one greather but one must be subtracted to account for the absolute value conversion
  // -3 = 1101   = sub1 =>  1100 = not => 0011 == 3 
  //
  const uint64_t bufMax = 9999999999999999998UL;
  return ~(bufMax-n1-n2);
}

void buffersEaqualize(bigNumber* n1, bigNumber*  n2, bigNumber* n3){
  int maxBufLen = n1->blockCount;
  if(maxBufLen < n2->blockCount){
    maxBufLen = n2->blockCount;
  }
  if(maxBufLen < n3->blockCount){
    maxBufLen = n3->blockCount;
  }

  n1->extend(maxBufLen-n1->blockCount, true);
  n2->extend(maxBufLen-n2->blockCount, true);
  n3->extend(maxBufLen-n3->blockCount, true);

}


void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest){
  buffersEaqualize(n1, n2, dest);
  
  uint64_t* n1mem =  n1->memory;
  uint64_t* n2mem =  n2->memory;
  uint64_t* n3mem =  dest->memory;
  

}
