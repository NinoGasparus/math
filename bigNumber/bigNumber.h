#ifndef bignumber
#define bignumber

#include <cstdint>
#include <fstream>
#include <string>
class bigNumber{
public:
  uint64_t* memory;
  uint64_t size;  
  uint64_t exp;
  uint64_t blockCount;
};

#endif 

