#include <stdio.h>

#include "calc3.h"

#include "y.tab.h"

static int lbl;

int ex(nodeType * p) {
  int lbl1, lbl2;

  if (!p) return 0;
  switch (p -> type) {
  case typeCon:
    printf("\tpush\t$%d\n", p -> con.value); // hanterar värde a.k.a 
    break;
  case typeId:
    printf("\tpush\t%c\n", p -> id.i + 'a');
    break;
  case typeOpr:
    switch (p -> opr.oper) {
    case WHILE:
      printf("L%03d:\n", lbl1 = lbl++);
      ex(p -> opr.op[0]);
      printf("\tjz\tL%03d\n", lbl2 = lbl++);
      ex(p -> opr.op[1]);
      printf("\tjmp\tL%03d\n", lbl1);
      printf("L%03d:\n", lbl2);
      break;
    case IF:
      ex(p -> opr.op[0]);
      if (p -> opr.nops > 2) {
        /* if else */
        printf("\tjz\tL%03d\n", lbl1 = lbl++);
        ex(p -> opr.op[1]);
        printf("\tjmp\tL%03d\n", lbl2 = lbl++);
        printf("L%03d:\n", lbl1);
        ex(p -> opr.op[2]);
        printf("L%03d:\n", lbl2);
      } else {
        /* if */
        printf("\tjz\tL%03d\n", lbl1 = lbl++);
        ex(p -> opr.op[1]);
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
      printf("\tpop\t%c\n", p -> opr.op[0] -> id.i + 'a');
      break;
    case UMINUS:
      ex(p -> opr.op[0]);
      printf("\tneg\n");
      break;

    case FACT:

      ex(p -> opr.op[0]);
	  printf("\t ### printing ###  \n");
	  printf("\tpopq\t%%r12\n");
      printf("\tcall\tfactorial\n");
      break;

    case LNTWO:
      ex(p -> opr.op[0]);
      printf("\\lntwo\n");
      break;
    default:
      ex(p -> opr.op[0]);
      ex(p -> opr.op[1]);
      switch (p -> opr.oper) {
      case GCD:
        printf("\tgcd\n");
        break;

      case '+':
        printf("\t ### addding ###  \n");
        printf("\tpopq \t %%r8\n");
        printf("\tpopq \t %%r9\n");
        printf("\taddq \t %%r8,%%r9\n");
        printf("\tpushq \t%%r9\n");
        break;

      case '-':
		printf("\txorq \t%%r8, %%r8\n");
		printf("\tpopq \t %%r8\n");
		printf("\tsub\t%%r8, %%rax\n");
        break;
        printf("\t ### subtracting ###  \n");
        printf("\tpopq \t %%r8\n");
        printf("\tpopq \t %%r9\n");
        printf("\tsubq \t %%r8,%%r9\n");
        printf("\tpushq \t%%r8\n");

      case '*':
        printf("\tmul\n");
        break;
        printf("\t ### multiplication ###  \n");
        printf("\tpopq \t %%r8\n");
        printf("\tpopq \t %%r9\n");
        printf("\timulq \t %%r8,%%r9\n");
        printf("\tpushq \t%%r8\n");

      case '/':
        printf("\t##### division ####### \n");
        printf("\tpopq \t %%r8\n"); // första värdet poppas till r8
        printf("\tpopq \t %%r9\n"); // andra värdet poppas till r9
        printf("\txorq \t%%rax, %%rax\n");
        printf("\tmovq \t%%r8, %%rax\n");
        printf("\tcqto\n");
        printf("\tidivq\t%%r9\n");
        printf("\tpushq\t%%rax\n");

        break;
      case '<':
        printf("\tcompLT\n");
        break;
      case '>':
        printf("\tcompGT\n");
        break;
      case GE:
        printf("\tcompGE\n");
        break;
      case LE:
        printf("\tcompLE\n");
        break;
      case NE:
        printf("\tcompNE\n");
        break;
      case EQ:
        printf("\tcompEQ\n");
        break;
      }
    }
  }
  return 0;
}