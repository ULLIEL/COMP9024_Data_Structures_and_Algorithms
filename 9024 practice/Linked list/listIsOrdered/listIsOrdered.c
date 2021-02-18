
#include "list.h"

bool listIsOrdered(List l) {
	Node curr = l->head;
	
	if (curr == NULL || curr->next == NULL){
		return true;
	}
	int n = ((curr->value) > (curr->next->value));
	
	while (curr->next != NULL){
		if ((curr->value) > (curr->next->value) != n){
			return false;
		}
		curr = curr->next;
	}
	return true;
}

