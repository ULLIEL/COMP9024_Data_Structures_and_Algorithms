
#include "list.h"

bool listIsPalindromic(List l) {
	Node left = l->first, right = l->last;

	while(left != right && right->next != left){
		if (left->value != right->value){
			return false;
		}
		left = left->next;
		right = right->prev;
	}
	return true;
}


 
