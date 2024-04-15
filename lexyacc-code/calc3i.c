#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;

void comp(int n);

int ex(nodeType * p) {
  int lbl1, lbl2;

  if (!p) return 0;
  switch (p -> type) {
  case typeCon:
    printf("\tpush\t$%d\n", p -> con.value);
    break;
  case typeId:
    printf("\tpush\t%c\n", p -> id.i + 'a');
    break;
  case typeOpr:
    switch (p -> opr.oper) {
    case WHILE:
      printf("\t ### CASE WHILE ###  \n");
      printf("L%03d:\n", lbl1 = lbl++);
      ex(p -> opr.op[0]);
      printf("L%03d\n", lbl2 = lbl++);
      ex(p -> opr.op[1]);
      printf("\tjmp\tL%03d\n", lbl1);
      printf("L%03d:\n", lbl2);
      break;
    case IF:
	printf("\t ### CASE IF ###  \n");
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) { 
                printf("L%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++); 
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
      break;
    case PRINT: //********  
      ex(p -> opr.op[0]);
      printf("\t ### printing ###  \n");

      printf("\txorq\t%%rdi, %%rdi\n");
      printf("\txorq\t%%rsi, %%rsi\n");
      printf("\tmovq\t$format, %%rdi\n");
      printf("\tmovq\t%%rax, %%rsi\n");

      printf("\txor\t%%rax, %%rax\n");

      printf("\tcall\tprintf\n");

      printf("\txor\t%%rsi, %%rsi\n");
      printf("\txor\t%%rdi, %%rdi\n");

      break;
    case '=':
      ex(p -> opr.op[1]);
	printf("\t ### EQUAL = ###  \n");
      printf("\tpop\t%c\n", p -> opr.op[0] -> id.i + 'a');
      break;
    case UMINUS:
      ex(p -> opr.op[0]);
    printf("\t ### UMINUS ###  \n");
      printf("\tpopq %%rax\n");
      printf("\tneg %%rax\n");
      printf("\tpushq %%rax\n");
      break;

    case FACT:

      ex(p -> opr.op[0]);
	  printf("\t ### factorial ###  \n");
	  printf("\tpopq\t%%r12\n");
      printf("\tcall\tfactorial\n");
      printf("\tpushq\t%%rax\n");
      break;

    case LNTWO:
	printf("\t ### LNTWO ###  \n");
      ex(p -> opr.op[0]);
      printf("\\lntwo\n");
      break;
    default:
      ex(p -> opr.op[0]);
      ex(p -> opr.op[1]);
      switch (p -> opr.oper) {
      case GCD:
	printf("\t ### gcd ###  \n");
        printf("\tgcd\n");
        break;

      case '+':
        printf("\t ### addding ###  \n");
      printf("\txorq\t%%rax, %%rax\n");
      printf("\txorq\t%%rbx, %%rbx\n");
        printf("\tpopq \t %%r8\n");
        printf("\tpopq \t %%r9\n");
        printf("\taddq \t %%r8,%%r9\n");
        printf("\tpushq \t%%r9\n");
        break;

      case '-':
        	printf("\t ### subtracting ###  \n");
      printf("\txorq\t%%rax, %%rax\n");
      printf("\txorq\t%%rbx, %%rbx\n");
		printf("\tpopq\t%%r11\n");
		printf("\tpopq\t%%r12\n");
		printf("\tsubq\t%%r11 , %%r12\n");
		printf("\tpushq\t%%r12\n");
        break;

      case '*':
        printf("\t ### multiplication ###  \n");
      printf("\txorq\t%%rax, %%rax\n");
      printf("\txorq\t%%rbx, %%rbx\n");
        printf("\tpopq \t %%rbx\n");
        printf("\tpopq \t %%rax\n");
        printf("\timulq \t %%rbx,%%rax\n");

        break;

      case '/':
        printf("\t##### division ####### \n");
       printf("\txorq\t%%rax, %%rax\n");
      printf("\txorq\t%%rbx, %%rbx\n");
        printf("\tpopq \t %%rbx\n"); // första värdet poppas till rbx
        printf("\tpopq \t %%rax\n"); // andra värdet poppas till rax
        printf("\tcqto\n");
	printf("\tidivq\t%%rbx\n"); // signed division of RDX:RAX / RBX
	printf("\tpushq\t%%rax\n");
        break;
      case '<':
        printf("\t ### <  ###  \n");
	comp(1);

        break;
      case '>':
        printf("\t ### >  ###  \n");
	comp(6);
        break;
      case GE:
        printf("\t ### GE  ###  \n");
        comp(2);
        break;
      case LE:
        printf("\t ### LE  ###  \n");
	comp(3); 
        break;
      case NE:
        printf("\t ### NE  ###  \n");
	comp(4);
        break;
      case EQ:
        printf("\t ### EQ  ###  \n");
        comp(5);
        break;
      }
    }
  }
  return 0;
}

void comp(int n) {
  if (n == 1){

        	printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tcmp\t%%rbx,%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetl\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
		printf("\tjz\t"); 
}
  if (n == 2){

        	printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetge\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
		printf("\tjz\t"); 
}

  if (n == 3){

        	printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetle\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
		printf("\tjz\t");
}

  if (n == 4){

                printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tmovq\t$1, %%r8\n");
		printf("\tmovq\t$0, %%r9\n");
		printf("\tcmpq\t%%rbx, %%rax \n");
		printf("\tcmoveq\t%%r8, %%r9\n");
		printf("\tjz\t"); 
}

  if (n == 5){
		printf("\txorq\t%%rbx,\t%%rbx\n"); 
                printf("\txorq\t%%rax,\t%%rax\n"); 
                printf("\tpopq\t%%rbx\n");
                printf("\tpopq\t%%rax\n");
                printf("\tcmpq\t%%rbx,\t%%rax\n"); 
                printf("\tjne\t"); 

}

  if (n == 6){
        	printf("\tpopq\t%%rbx\n");
		printf("\tpopq\t%%rax\n");
		printf("\tcmp\t%%rbx,%%rax\n");
		printf("\tmovq\t$0, %%rcx\n");
		printf("\tsetg\t%%cl\n");
		printf("\txorb\t$0, %%cl\n");
		printf("\tjz\t"); 

}

}

