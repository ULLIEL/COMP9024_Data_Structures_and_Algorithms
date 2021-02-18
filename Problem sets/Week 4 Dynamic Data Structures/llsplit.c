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

int GetListLength(NodeT *list){
    if (list == NULL){
        return 0;
    }

    NodeT *p;
    p = list;
    int length = 0;
    while(p != NULL){
        length++;
        p = p->next;

    }
    return length;
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

void printLL(NodeT *list, int length) {
    NodeT *p;
    p = list;
    int first_number = 0;
    int second_number = 0;
    int i = 0;
    if(length % 2 == 0){
           first_number = length/2;
           second_number = first_number;
       }
       else{
           first_number = length/2+1;
           second_number = length - first_number;
       }

    if (length == 0){
    }
    else{
        printf("\nFirst part is ");
        for (p = list; i < first_number; p = p->next){
            printf("%d", p->data);
            if(i < first_number-1)printf("->");
            i++;
        }
        if(second_number != 0){
            printf("\nSecond part is ");
            for (; p != NULL; p = p->next){
              printf("%d", p->data);
             if(p->next!=NULL)printf("->");
            }
        }
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

    int length = GetListLength(all);
    printLL(all,length);
}
