#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	int depth = 0;
	while (t->value != key){
		if (key < t->value){
			if (t->left == NULL){
				return -1;
			} else {
				t = t->left;
				depth ++;
			}
		} else if (key > t->value) {
			if (t->right == NULL){
				return -1;
			} else {
				t = t->right;
				depth ++;
			}
		}
	}
	return depth;
}

