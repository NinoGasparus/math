
#include "../bigNumber/bigNumber.h"
#include "../bigUtils/bigUtils.h"
#include <iostream>
#include <bitset>
void bigPrint(bigNumber number){
  for(int i = number.blockCount-1; i >=0; i--){
     if(number.memory[i] != 0){ 
     std::cout << number.memory[i];
     }else if (i != number.blockCount){
      std::cout  << "0000000000000000000";
    }
  }
}



void printMem(int id, bigNumber number){
  std::string of = "";
  if(id == -1){
    for(int i =0; i < number.blockCount; i++){
      std::cout << std::bitset<64>(number.memory[i]) << " => "  << number.memory[i] << of<<  '\n';
    }
  }else{
      std::cout << std::bitset<64>(number.memory[id]) << " => "  << number.memory[id] << of << '\n';
  }
}

void printMem(bigNumber number){
 printMem(-1, number);
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




extern "C" bool addRegisters(uint64_t* n1, uint64_t* n2, uint64_t*  dest);
 
  bool increment(uint64_t * number){
  uint64_t ok = 1;
    if(addRegisters(number,&ok , number)){
      increment(number+1);
    }else{
    return false;
  }return false;
  }



void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest){
 
  printf("2");
  buffersEaqualize(n1, n2, dest);
  
  uint64_t* n1mem =  n1->memory;
  uint64_t* n2mem =  n2->memory;
  uint64_t* n3mem =  dest->memory;
  uint64_t c= 0;
  bool of = 0;
  
printf("3");
  for(int i = 0; i < dest->blockCount; i++){
    of = addRegisters(&n1mem[i], &n2mem[i], &n3mem[i]);
    if(of){
      if(dest->blockCount <= i+1){
        dest->extend(1,true);
        n1->extend(1,true);
        n2->extend(1,true);
      }
      increment(&n1mem[i]+1);
    }
  }
}
