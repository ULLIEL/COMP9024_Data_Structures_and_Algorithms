
#include "list.h"

void reverseDLList(List l) {
	if (l != NULL && l->head != NULL){
		Node curr = l->head;
		Node temp;
		l->last = l->head;		
		
		while (curr->next != NULL){
			temp = curr->next;
			curr->next = curr->prev;
			curr->prev = temp;
			curr = temp;
		}		
		curr->next = curr->prev;
		curr->prev = NULL;
		l->head = curr;
	}
}


