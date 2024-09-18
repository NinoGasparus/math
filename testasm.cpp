#include <iostream>
#include <cstdint>
#include <bitset>
int main() {
    uint64_t x = ~0-49;
    uint64_t y = 50;
    uint64_t z = 0; 
    uint64_t q = 0;
 asm volatile (
        "mov $0, %%rcx      \n\t" //rcx = 0
        "mov %[y], %%rax    \n\t" //rax = y
        "mov %[x], %%rbx    \n\t" //rbx = x
        "add %%rax, %%rcx   \n\t" //rcx += rax 
        "add %%rbx, %%rcx   \n\t" //rcx += rbx
        "mov %%rcx, %[z]    \n\t" // z  = rcx 
        
        "pushf              \n\t" //load eflags to stack
        "pop %%rax          \n\t" //pop eflags from stack into rax
        "mov $1, %%rbx     \n\t" //rbx = ...bitmask
        "and %%rbx, %%rax   \n\t"
      //  "shr $4, %%rax     \n\t"
        "mov %%rax, %[q]    \n\t" //q = rax
        
        : [z] "=r" (z),
          [q] "=r" (q)
        
        : [x] "r" (x),
          [y] "r" (y)
        : "cc", "rax", "rbx", "rcx"                               
  );
    std::cout << "z = " << z << std::endl;
    std::cout << "q = " << std::bitset<64>(q) << std::endl; 
    if(q == 1){
      printf("worked\n");
    }
  
    return 0;
}

