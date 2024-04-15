.section .data
.section .text
.globl factorial
factorial:
      movq    %r12, %rax
      cmpq $0, %rax
      jle onexit
factorial_loop:
      sub    $1, %r12
      cmpq    $1, %r12
      jle     exit
	  imul    %r12, %rax
      jmp     factorial_loop
exit:
      ret
onexit:
	movq $1, %rax
	ret
