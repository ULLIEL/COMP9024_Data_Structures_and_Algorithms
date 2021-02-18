// Binary Search Tree ADT Tester ... COMP9024 19T3

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"

#define MAX_STR_LEN 20

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
    int data;
    Tree left, right;
} Node;

// make a new node containing data
Tree newNode(Item it) {
    Tree new = malloc(sizeof(Node));
    assert(new != NULL);
    data(new) = it;
    left(new) = right(new) = NULL;
    return new;
}

// create a new empty Tree
Tree newTree() {
    return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
    if (t != NULL) {
        freeTree(left(t));
        freeTree(right(t));
        free(t);
    }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
    if (t != NULL) {
        showTreeR(right(t), depth + 1);
        int i;
        for (i = 0; i < depth; i++)
            putchar('\t');            // TAB character
        printf("%d\n", data(t));
        showTreeR(left(t), depth + 1);
    }
}

void showTree(Tree t) {
    showTreeR(t, 0);
}

// compute height of Tree
int TreeHeight(Tree t) {
    if (t == NULL)
        return 0;
    else{
        int lHeight = TreeHeight(left(t));
        int rHeight = TreeHeight(right(t));

        if(lHeight > rHeight)
            return (lHeight+1);
        else return (rHeight+1);
    }
}

int TreeWidth(Tree t) {

    // not yet implemented

}

// count #nodes in Tree
int TreeNumNodes(Tree t) {
    if (t == NULL)
        return 0;
    else
        return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
    if (t == NULL)
        return false;
    else if (it < data(t))
        return TreeSearch(left(t), it);
    else if (it > data(t))
        return TreeSearch(right(t), it);
    else                                 // it == data(t)
        return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
    if (t == NULL)
        t = newNode(it);
    else if (it < data(t))
        left(t) = TreeInsert(left(t), it);
    else if (it > data(t))
        right(t) = TreeInsert(right(t), it);
    return t;
}

Tree joinTrees(Tree t1, Tree t2) {
    if (t1 == NULL)
        return t2;
    else if (t2 == NULL)
        return t1;
    else {
        Tree curr = t2;
        Tree parent = NULL;
        while (left(curr) != NULL) {    // find min element in t2
            parent = curr;
            curr = left(curr);
        }
        if (parent != NULL) {
            left(parent) = right(curr);  // unlink min element from parent
            right(curr) = t2;
        }
        left(curr) = t1;
        return curr;                    // min element is new root
    }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
    if (t != NULL) {
        if (it < data(t))
            left(t) = TreeDelete(left(t), it);
        else if (it > data(t))
            right(t) = TreeDelete(right(t), it);
        else {
            Tree new;
            if (left(t) == NULL && right(t) == NULL)
                new = NULL;
            else if (left(t) == NULL)    // if only right subtree, make it the new root
                new = right(t);
            else if (right(t) == NULL)   // if only left subtree, make it the new root
                new = left(t);
            else                         // left(t) != NULL and right(t) != NULL
                new = joinTrees(left(t), right(t));
            free(t);
            t = new;
        }
    }
    return t;
}

void help();

int main(void) {
    Tree mytree = newTree();

    bool noShow = false;
    char line[MAX_STR_LEN];
    printf("\n> ");
    while (fgets(line, MAX_STR_LEN, stdin) != NULL) {
        int value = atoi(&line[1]);
        switch (line[0]) {

            case 'n':
                freeTree(mytree);
                mytree = newTree();
                break;

            case 'i':
                mytree = TreeInsert(mytree, value);
                break;

            case 'd':
                mytree = TreeDelete(mytree, value);
                break;

            case 's':
                if (TreeSearch(mytree, value))
                    printf("Found!\n");
                else
                    printf("Not found\n");
                noShow = true;
                break;

            case 'q':
                printf("Bye.\n");
                freeTree(mytree);
                return 0;

            default:
                help();
                noShow = true;
        }

        if (noShow) {
            noShow = false;
            printf("\n> ");
        } else {
            printf("New Tree:");
            printf("  #nodes = %d,", TreeNumNodes(mytree));
            printf("height = %d\n", (TreeHeight(mytree)-1));
            if (TreeHeight(mytree) < 8)
                showTree(mytree);
            else
                printf("New Tree is too deep to display nicely\n");
            printf("\n> ");
        }
    }

    freeTree(mytree);
    return 0;
}

void help() {
    printf("Commands:\n");
    printf("n = make a new tree\n");
    printf("i N = insert N into tree\n");
    printf("d N = delete N from tree\n");
    printf("s N = search for N in tree\n");
    printf("q = quit\n");
}
