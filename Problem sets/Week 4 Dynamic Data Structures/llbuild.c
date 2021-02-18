#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct node {
   int data;
   struct node *next;
} NodeT;

NodeT *makeNode(int v) {
   NodeT *new = malloc(sizeof(NodeT));
   assert(new != NULL);
   new->data = v;       // initialise data
   new->next = NULL;    // initialise link to next node
   return new;          // return pointer to new node
}

void freeLL(NodeT *list) {
   NodeT *p, *temp;
   p = list;
   while (p != NULL) {
      temp = p->next;
      free(p);
      p = temp;
   }
}

void showLL(NodeT *list) {
   NodeT *p;
   if (list == NULL){
   printf("Done.");
   }
   else{
       printf("Done. List is ");
       for (p = list; p != NULL; p = p->next){
       printf("%d", p->data);
       if(p->next!=NULL)printf("->");
       }
    }
}

NodeT *joinLL(NodeT *list1, NodeT *list2){
    NodeT *p;
    if(list1 == NULL){
        return list2;
    }
    else {
        for(p = list1; p->next != NULL; p=p->next);
        p->next = list2;
        return list1;
    }
}

int main(){
    NodeT *all = NULL;
    int num;

    printf("Enter an integer: ");
    int status = scanf("%d", &num);

    while(status == 1){
    NodeT *number = makeNode(num);
    all = joinLL(all,number);

    printf("Enter an integer: ");
    status = 0;
    status = scanf("%d", &num);
    }
    showLL(all);
}
