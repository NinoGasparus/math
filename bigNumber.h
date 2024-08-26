#include <string>
class bigNumber{
public:
  void init();
  void loadStr(std::string number);
private:
  uint64_t* memory;
  uint64_t size;  
  uint64_t exp;
  uint64_t blockCount;
};

