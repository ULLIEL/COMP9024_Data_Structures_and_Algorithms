
#include "list.h"

void listReverse(List l) {
	if (l->head != NULL && l->head->next != NULL){
		Node curr = l->head;
		Node prev = NULL, nextnode = curr->next;
		while (nextnode != NULL){
			nextnode = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextnode;
		}
		l->head = prev;
	}
}

