global smartAdd

section  .text
smartAdd:
  mov rax, rdi; rax = x
  mov rbx, rsi; rbx = y
  
  add rax, rbx; rax += rbx
  mov [rdx], rax; store rax into ram @rdx 

  pushf; push EFlags tostack
  pop rax; pop topStack item to rax
  
  and rax, 1; and rax with 1 if 0thflag is 0 return 0 else return 1

  ret;
