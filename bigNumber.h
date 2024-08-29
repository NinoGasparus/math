#include <fstream>
#include <string>
class bigNumber{
public:
  void init();
  void loadStr(std::string number);
  void loadFile(std::ifstream fileHandle);
  void extend(int chunkCount, bool location); 
  

  uint64_t* memory;
  uint64_t size;  
  uint64_t exp;
  uint64_t blockCount;
};

void printMem(int id, bigNumber number);
void printMem(bigNumber number);

void bigPrint(bigNumber number);
