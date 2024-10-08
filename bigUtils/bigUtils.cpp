#include "../bigNumber/bigNumber.h"
#include "../bigUtils/bigUtils.h"
#include <cmath>
#include <cstring>

int DEFBUFSIZE = 1;
int REGSIZE = 8;
int PRECISION = 19;
void init(bigNumber number){ 
  number.memory = new uint64_t[DEFBUFSIZE];
  std::memset(number.memory, 0, DEFBUFSIZE * REGSIZE);
  number.exp = 0;   
  number.size = 0;
  number.blockCount = 0; 
}

uint64_t betterPOW(int exp) {
    uint64_t base = 1;
    for (int i = 0; i < exp; i++) {
        base *= 10;
    }
    return base;
}

void  loadStr(bigNumber number , std::string string){
  int size = string.size();
  number.blockCount = std::floor(size / PRECISION) +1;
  //realocate new memory are with more space
  if(number.blockCount > DEFBUFSIZE){
    delete [] number.memory;
    number.memory =new uint64_t[number.blockCount];
    std::memset(number.memory, 0, number.blockCount*REGSIZE);
  }
  //subtract binary 0 from every character of the number to convert them to their b10 representations
  for(int i = 0; i < size; i++){
   string[i] = string[i] - '0';
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
     number.memory[bufIndex] += betterPOW(exp) * string[(size -1) - (i * PRECISION + j)];
      exp++;
    }
    exp = 0;
    bufIndex ++;
  }
  
}

void bigNumber::loadFile(std::string filename){

  std::ifstream fileHandle(filename);
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
