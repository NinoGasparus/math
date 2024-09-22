#include "bigNumber.h"
#include <csignal>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <bitset>
#include <memory>
#include <ostream>
#include <sys/types.h>







const uint64_t bufMax = 10000000000000000000UL;

void bigPrint(bigNumber number){
  for(int i = number.blockCount-1; i >=0; i--){
     if(number.memory[i] != 0){ 
     std::cout << number.memory[i];
     }else if (i != number.blockCount){
      std::cout  <<  "0000000000000000000";
    }
  }
}



void printMem(int id, bigNumber number){
  std::string of = "";
  if(id == -1){
    for(int i =0; i < number.blockCount; i++){
      if(number.memory[i] > bufMax){ 
        of = " OF ";
      }else{
        of = "    ";
      }
      std::cout << std::bitset<64>(number.memory[i]) << " => "  << number.memory[i] << of<<  '\n';
    }
  }else{
    if(number.memory[id] > bufMax){
      of = " OF ";
    }else{
      of = "    ";
    }
      std::cout << std::bitset<64>(number.memory[id]) << " => "  << number.memory[id] << of << '\n';
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
  return ~((bufMax-1)-n1-n2);
}

void buffersEaqualize(bigNumber* n1, bigNumber*  n2, bigNumber* n3){
  int maxBufLen = n1->blockCount;
  if( n1->blockCount == n2->blockCount && n1->blockCount == n3->blockCount){
    return;
  }
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




extern "C" bool addRegisters(uint64_t n1, uint64_t n2, uint64_t*  dest, uint64_t regcount);

void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest){
  buffersEaqualize(n1, n2, dest);
  
  uint64_t* n1mem =  n1->memory;
  uint64_t* n2mem =  n2->memory;
  uint64_t* n3mem =  dest->memory;
  
  int c= 0;
  uint64_t overflow = 0;


  while(true){
    if(addRegisters(n1mem[c], n2mem[c], n3mem,0)){
      overflow ++;
    }
    if(overflow != 0){
      uint64_t tmpcounter = c;
      while(true){
        if(tmpcounter == dest->blockCount){
          dest->extend(1, true);
          
        }
        if(overflow ==  0){
          break;
        }else{
          if(addRegisters(n1mem[tmpcounter], overflow,n1mem+tmpcounter , 0)){
            overflow = 1;
            tmpcounter++;
          }else{
            overflow = 0;
          }
        }
      }
    }
  } 


}
