global addRegisters

  section .text

;input
;rdi-n1, first number (uint64_T array)
;rsi-n2, second number (uint64_t array)
;rdx-dest, where to put  resoult (uint64_t array)
; UNUSED  rcx-regcount, how many  registers starting  at n1 to add (n1->n1+regcount)
;returns 0 if  no overflow  occured on the last addition otherwise returns 1
addRegisters:

  




  add rdi, rsi ; rdi = sum of the n1 and n2
  
  pushf   ;  push EFlags to stack
  pop rax ;  pop EFlags from stack to rax
  
  and rax, 0x1;  AND rax and 0x1 into rax, expected to be 1 if CF is set or 0 if CF is  not set
  ;if addition overflew rax will be  1 and  function will return ture else it returns  false
  
  mov [rdx], rdi;  store the sum of n1 and  n2 into dest. 
ret
