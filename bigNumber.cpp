#include "bigNumber.h"
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstring>
#include <exception>
#include <fstream>
#include <stdio.h>
#include <string>
#include <bitset>
#include <iostream>
//number of  digits (b10) that can fit inside the default memory unit (64bits) without the possibility of overflow 
const int PRECISION = 19;
//default lenght of the memory used to store the number in units of  DEFBUFSIZE bytes 
const int DEFBUFSIZE = 10;

//size of base register in bytes (largest word cpu can process) 64bit cpus - 8 32bit cpus - 4. 
//AVX = 16 
//AVX2= 32
//AVX512 = 64
int REGSIZE = 8;

void bigNumber::init(){
  memory = new uint64_t[DEFBUFSIZE]; 
  std::memset(memory, 0, DEFBUFSIZE * REGSIZE);

  
  exp = 0;   
  size = 0;
  blockCount = 0; 
}

uint64_t betterPOW(int exp) {
    uint64_t base = 1;
    for (int i = 0; i < exp; i++) {
        base *= 10;
    }
    return base;
}

void  bigNumber::loadStr(std::string number){
  size = number.size();
 blockCount = std::floor(size / PRECISION) +1;
  //realocate new memory are with more space
  if(blockCount > DEFBUFSIZE){
    delete [] memory;
    memory =new uint64_t[blockCount];
    std::memset(memory, 0, blockCount*REGSIZE);
  }
  
  //subtract binary 0 from every character of the number to convert them to their b10 representations
  for(int i = 0; i < size; i++){
    number[i] = number[i] - '0';
  }

  int bufIndex = 0;
  int tmpExp = 0;
  int chunkSize = PRECISION; 

  for(int i = 0; i < (int)size / PRECISION + 1; i++){
    if(i * PRECISION + PRECISION > size-1){
      chunkSize = size - i * PRECISION; 
    }else{ 
      chunkSize = PRECISION;
    }

    for(int j = 0; j < chunkSize; j++){
     memory[bufIndex] += betterPOW(exp) * number[(size -1) - (i * PRECISION + j)];
      exp++;
    }
    exp = 0;
    bufIndex ++;
  }
  
}

void bigNumber::loadFile(std::ifstream fileHandle){
  try{
    if(!fileHandle){
      throw std::exception();
    }else{
      std::string s;
      fileHandle >> s;
      loadStr(s);
      fileHandle.close();
    }
  }catch(std::exception e){
      printf("Error loading file");
  }
}

void bigNumber::extend(int chunkCount, bool location){
  //if true  extend in  front  else extend  from  the back  
  if(location){
    uint64_t* newMemory = new uint64_t[blockCount+chunkCount];
    memset(newMemory+blockCount, 0,chunkCount * REGSIZE);
    memcpy(newMemory,memory, blockCount*REGSIZE);

    delete[] memory;
    blockCount =  this->blockCount + chunkCount;
    this->memory = newMemory;


  }else{
    uint64_t* newMemory = new uint64_t[blockCount+chunkCount];

    memset(newMemory, 0, chunkCount * REGSIZE);
    memcpy(newMemory+chunkCount ,memory, blockCount*REGSIZE);

    delete[] memory;
    this->memory = newMemory;
    blockCount = this->blockCount + chunkCount;
  }

}

