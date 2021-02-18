#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) {
		return NULL;
	} else {
		if (t->left != NULL) {
			return BSTreeGetSmallest(t->left);
		} else {
			return t;
		}
	}
}



