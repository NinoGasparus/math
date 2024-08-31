#include "bigNumber.h"
#include <csignal>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <bitset>
#include <ostream>
#include <sys/types.h>







const uint64_t bufMax = 9999999999999999999UL;

void bigPrint(bigNumber number){
  for(int i = number.blockCount-1; i >=0; i--){
      std::cout << number.memory[i];
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






void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest){
  buffersEaqualize(n1, n2, dest);
  
  uint64_t* n1mem =  n1->memory;
  uint64_t* n2mem =  n2->memory;
  uint64_t* n3mem =  dest->memory;
  
  uint64_t bufCounter = 0;
  uint64_t overflow = 0;

  uint64_t tmpVar = 0;
  bool tryOverflow =  false;
  while( bufCounter != n1->blockCount){
    
    //test compute
    if(overflow  != 0){
      //in case previous pass of the loop encoutered an  overflow add it to one of buffers
      tmpVar = overflow+n1mem[bufCounter];
      if(tmpVar > bufMax || tmpVar < n1mem[bufCounter] || tmpVar < overflow){
        //cant be added to first number, try second
        tmpVar = overflow+n2mem[bufCounter];

        if(tmpVar > bufMax || tmpVar < n2mem[bufCounter] || tmpVar < overflow){
        //second dont work either carry it on
        //try to add at end of compute 
        tryOverflow = true;
        }else{
          n2mem[bufCounter] +=overflow;
          overflow = 0;
        }
      }else{
        n1mem[bufCounter] += overflow;
        overflow = 0;
      }
      tmpVar = 0;

    }



    n3mem[bufCounter] = n1mem[bufCounter] + n2mem[bufCounter];
    if( n3mem[bufCounter] > bufMax || n3mem[bufCounter] < n1mem[bufCounter] || n3mem[bufCounter] < n2mem[bufCounter]){
      //overflow, cant add
      std::cout << "OF! " << n1mem[bufCounter]  << " + " << n2mem[bufCounter] << " exceeds by " << getOverflow(n1mem[bufCounter] , n2mem[bufCounter]) << '\n';
      n3mem[bufCounter] = getOverflow(n1mem[bufCounter] , n2mem[bufCounter]);
      overflow++;
    }

    if(tryOverflow){
      //figure out how much more we can go untill we reach bufmax value and reduce overflow by such
      tmpVar = bufMax - n3mem[bufCounter]; 
      n3mem[bufCounter] = bufMax;
      overflow -= tmpVar;
      tryOverflow = false;
    }
    bufCounter++;

  }

}
