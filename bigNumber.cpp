#include "bigNumber.h"
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <string>


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
  this->memory = new uint64_t[DEFBUFSIZE]; 
  std::memset(this->memory, 0, DEFBUFSIZE * REGSIZE);

  
  this->exp = 0;   
  this->size = 0;
  this->blockCount = 0; 
}

uint64_t betterPOW(int exp) {
    uint64_t base = 1;
    for (int i = 0; i < exp; i++) {
        base *= 10;
    }
    return base;
}

void  bigNumber::loadStr(std::string number){
  this->size = number.size();
  this->blockCount = std::floor(this->size / PRECISION) +1;
  //realocate new memory are with more space
  if(this->blockCount > DEFBUFSIZE){
    delete [] this->memory;
    this->memory =new uint64_t[this->blockCount];
    std::memset(this->memory, 0, this->blockCount*REGSIZE);
  }
  
  //subtract binary 0 from every character of the number to convert them to their b10 representations
  for(int i = 0; i < this->size; i++){
    number[i] = number[i] - '0';
  }

  int bufIndex = 0;
  int tmpExp = 0;
  int chunkSize = PRECISION; 

  for(int i = 0; i < (int)this->size / PRECISION + 1; i++){
    if(i * PRECISION + PRECISION > this->size-1){
      chunkSize = this->size - i * PRECISION; 
    }else{ 
      chunkSize = PRECISION;
    }

    for(int j = 0; j < chunkSize; j++){
      this->memory[bufIndex] += betterPOW(exp) * number[(this->size -1) - (i * PRECISION + j)];
      exp++;
    }
    exp = 0;
    bufIndex ++;
  }
  
}


