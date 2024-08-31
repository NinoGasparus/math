#include "bigNumber.h"
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <bitset>
#include <ostream>
#include <sys/types.h>







const uint64_t bufMax = 9999999999999999999UL;

void bigPrint(bigNumber number){
  bool leadingZero = true;
  for(int i = number.blockCount-1; i >=0; i--){
    if(number.memory[i] == 0 &&  leadingZero){
      
    }else if(number.memory[i] != 0 && leadingZero){
      leadingZero = false;
      std::cout << number.memory[i];
    }else{
    std::cout << number.memory[i];
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

void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest){
  buffersEaqualize(n1, n2, dest);
  
  uint64_t* n1mem =  n1->memory;
  uint64_t* n2mem =  n2->memory;
  uint64_t* n3mem =  dest->memory;
  
  uint64_t buffCounter = 0;
  uint64_t overflow = 0;
  while(true){
    
    //add buffers
    n3mem[buffCounter] =  n1mem[buffCounter] + n2mem[buffCounter];
    
 //   std:: cout << n1mem[buffCounter]  << " + " << n2mem[buffCounter] << " => " << n3mem[buffCounter] <<std::endl;
    //if overflow  increase 
    if(n3mem[buffCounter] > bufMax  ||  n3mem[buffCounter] < n1mem[buffCounter] || n3mem[buffCounter] < n2mem[buffCounter]){
      n3mem[buffCounter] = getOverflow(n1mem[buffCounter], n2mem[buffCounter]);
      //std::cout << "of\n"; 
      overflow ++;

    }
    buffCounter++;
    if(overflow != 0){
      uint64_t tempCounter = buffCounter;
      //try to increment n1mem by overflow
      while(true){
      tryAgain:
        n1mem[tempCounter] += overflow;
        if(n1mem[tempCounter] > bufMax || n1mem[tempCounter] < n1mem[tempCounter] - overflow || n1mem[tempCounter] < overflow){
          //overflow carry on
          n1mem[tempCounter] = getOverflow(n1mem[tempCounter] - overflow, overflow);
          overflow = 1;
          tempCounter ++;
          goto tryAgain;
          
        }else{
          //all ok
          break;
        }
      }
      
    }
    //by here overflow must  be 0
    //default  case
    if(buffCounter == n1->blockCount){
      break;
    }
  }

}
