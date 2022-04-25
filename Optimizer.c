#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
 {
 	Instruction *head;
 	head = ReadInstructionList(stdin);
 	if (!head) {
 		ERROR("No instructions\n");
 		exit(EXIT_FAILURE);
 	}

	/* YOUR CODE GOES HERE */

 	Instruction *y;
 	Instruction *z;
 	Instruction *x;

	Instruction *instr = head;

	do {
		y = instr;
		z = instr->next;
		x = z->next;
		if (y->opcode == LOADI && z->opcode == LOADI) {
			switch (x->opcode) {
				case ADD:
					if ((y->field1 == x->field3 && z->field1 == x->field2)||(y->field1 == x->field2 && z->field1 == x->field3)) {
						instr->field1 = x->field1;
						instr->field2 = y->field2 + z->field2;
						instr->next = x->next;
						x->next->prev = instr;
						free(z);
						free(x);
					}		
					break;
				case SUB:
					if (y->field1 == x->field2 && z->field1 == x->field3) {
						instr->field1 = x->field1;
						instr->field2 = y->field2 - z->field2;
						instr->next = x->next;
						x->next->prev = instr;
						free(z);
						free(x);
					}
					break;
				case MUL:
					if ((y->field1 == x->field2 && z->field1 == x->field3) || (y->field1 == x->field3 && z->field1 == x->field2)) {
						instr->field1 = x->field1;
						instr->field2 = y->field2 * z->field2;
						instr->next = x->next;
						x->next->prev = instr;
						free(z);
						free(x);
					}		
					break;		
				case OR:
					if (y->field1 == x->field2 && z->field1 == x->field3){
						instr->field1 = x->field1;
						instr->field2 = (y->field2 | z->field2);
						instr->next = x->next;
						x->next->prev = instr;
						free(z);
						free(x);
					}
					break;
				case XOR:
					if (y->field1 == x->field2 && z->field1 == x->field3){
						instr->field1 = x->field1;
						instr->field2 = (y->field2 ^ z->field2);
						instr->next = x->next;
						x->next->prev = instr;
						free(z);
						free(x);
					}
					break;
				default:
					break;
			}
		}
		instr = instr->next;
	} while (instr != NULL && instr->next != NULL && instr->next->next != NULL);

 	PrintInstructionList(stdout, head);
 	DestroyInstructionList(head);
 	return EXIT_SUCCESS;
}

