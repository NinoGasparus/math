#include <cstdint>
#include <fstream>
#include <string>
class bigNumber{
public:
  void init();
  void loadStr(std::string number);
  void loadFile(std::string filename);
  void extend(int chunkCount, bool location); 
  

  uint64_t* memory;
  uint64_t size;  
  uint64_t exp;
  uint64_t blockCount;
};

void printMem(int id, bigNumber number);
void printMem(bigNumber number);

void bigPrint(bigNumber number);

uint64_t getOverflow(uint64_t  n1, uint64_t n2);
void buffersEaqualize(bigNumber* n1, bigNumber* n2, bigNumber* n3);

void bigAdd(bigNumber* n1, bigNumber* n2,  bigNumber* dest);



