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
uint64_t addBuffers(uint64_t b1, uint64_t b2, uint64_t* dest){
  *dest = b1 + b2;
  if(*dest  < b1 || *dest < b2){
    *dest = getOverflow(b1, b2);
    return 1;
  }
  return  0;
}




uint64_t addRegisters(uint64_t*  n1, uint64_t* n2, uint64_t*  dest){
  uint64_t t1 =  *n1;
  uint64_t t2 =  *n2;
  uint64_t d  =  *dest;

    d = t1 + t2;
    if( d >= bufMax || d < t1 || d < t2){
      //overflow, cant add
    //  std::cout << "OF! " << t1 << " + " << t2 << " exceeds by " << getOverflow(t1, t2) << " of:";
      d= getOverflow(t1,t2);
      *dest = d;
     return 1;
    }else{
      *dest = *n1 +  *n2;
      return 0;
    }
  }


void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest){
  buffersEaqualize(n1, n2, dest);
  
  uint64_t* n1mem =  n1->memory;
  uint64_t* n2mem =  n2->memory;
  uint64_t* n3mem =  dest->memory;
  
  uint64_t bufCounter = 0;
  uint64_t overflow = 0;
  uint64_t TmpCounter = 0;

  while( bufCounter <= n1->blockCount){
    if(overflow != 0){
      TmpCounter = bufCounter;
      while(true){
        overflow = addRegisters(&n1mem[TmpCounter], &overflow, &n1mem[TmpCounter]);
        if(overflow != 0){
          TmpCounter++;
        }else{
          break;
        }
      }

    } 
    
    overflow = addRegisters(&n1mem[bufCounter] , &n2mem[bufCounter] , &n3mem[bufCounter]);
    bufCounter++;

  }

}
