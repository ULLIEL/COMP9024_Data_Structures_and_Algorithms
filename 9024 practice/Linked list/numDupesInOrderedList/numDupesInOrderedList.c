
#include "list.h"

int numDupesInOrderedList(List l) {
	Node curr = l->head;
	int num = 0;
	
	while (curr->next != NULL){
		if (curr->value == curr->next->value){
			num ++;
		}
		curr = curr->next;
	}
	return num;
}








