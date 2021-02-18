
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if (t == NULL){
        return -1;
    } else {
        int left = TreeHeight(t->left);
        int right = TreeHeight(t->right);
        if (left > right) {
            return 1 + left;
        } else {
            return 1 + right;
        }
    }
}





