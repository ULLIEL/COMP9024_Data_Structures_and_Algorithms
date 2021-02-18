#include <stdlib.h>

#include "BSTree.h"
//中序遍历
void BSTreeKth(BSTree t, int *k, int *result){
	if (t != NULL) {
		BSTreeKth(t->left, k, result);
		if (*k == 0) {
			*result = t->value;
		}
		*k = *k - 1;
		BSTreeKth(t->right, k, result);		
	}
}

int BSTreeGetKth(BSTree t, int k) {
	int result = -1;
	BSTreeKth(t, &k, &result);
	return result;
}
