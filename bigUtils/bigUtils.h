#include <string>
#include "../bigNumber/bigNumber.h"

void init(bigNumber number);
void loadStr(bigNumber number, std::string string);
void loadFile(std::string filename);
void extend(int chunkCount, bool location); 
void loadint(uint64_t number);
void printMem(int id, bigNumber number);
void printMem(bigNumber number);
void buffersEaqualize(bigNumber* n1, bigNumber* n2, bigNumber* n3);




