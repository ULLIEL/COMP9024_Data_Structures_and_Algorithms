
#include <stdlib.h>
#include <math.h>
#include "tree.h"

int TreeNodes(Tree t){
	if (t != NULL) {
		int left = TreeNodes(t->left);
		int right = TreeNodes(t->right);
		return 1 + left + right;
	}
	return 0;
}

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
		return true;
	} else {
		return TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right)
		&& (abs(TreeNodes(t->left) - TreeNodes(t->right)) <= 1);
		}
}
