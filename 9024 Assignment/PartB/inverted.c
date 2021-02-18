#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "DLList.h"

#define MAX_LINE 1000
#define FAIL "Fail to read!"


int main() {    
    char *token, line[MAX_LINE];
    char delim[6] = " .,;?", delims[2] = " ";
    int i, count, numberOfVertices = 0;
    FILE *fp, *fpr;
    char fileName[MAX_LINE];
    DLList invertedList = newDLList(), collectionUrls = newDLList();
    
    // Read the file collection.txt
    if ((fpr = fopen("collection.txt", "r")) == NULL){        
        perror("FAIL");
        exit(1);
    } else {
        while (fgets(line, MAX_LINE, fpr) != NULL) {
            line[strlen(line) - 1] = '\0';
            token = strtok(line, delims);

            while (token != NULL) {
                // insert token
                addDLList(collectionUrls, token);
                numberOfVertices++;
                // continue to get string
                token = strtok(NULL, delims);
            }
        }
        fclose(fpr);
    }

    // covert list to array
    char **urls = malloc(numberOfVertices * sizeof(char *));
    convertDLListToArray(collectionUrls, urls);
       
    for (i = 0; i < numberOfVertices; i++) {

        strcpy(fileName, urls[i]);
        strcat(fileName, ".txt");

        if ((fp = fopen(fileName, "r")) == NULL){
            perror("FAIL");
            exit(1);
        } else {
            line[strlen(line) - 1] = '\0';
            count = 0;
            while (fscanf(fp, "%s", line) != EOF){
                if (strcmp(line, "Section-2") == 0 || strcmp(line, "#end") == 0){
                    count ++;
                    continue;
                } if (count == 3){
                    break;
                } if (count == 2){
                    token = strtok(line, delim);
                    // lower every word
                    for (int j = 0; j < strlen(token); j++) {                        
                        if((token[j] >= 'a' && token[j]<='z') || token[j] == '-'){
                            continue;
                        } else if(token[j] >= 'A' && token[j]<='Z'){
                                token[j] -= ('A' - 'a');
                                continue;
                        }
                    }
                    addDLListAndChild(invertedList, token, urls[i]);
                    // continue to get string
                    token = strtok(NULL, delim);        
                    }
                }
            fclose(fp);
        }
    }

    sortDLList(invertedList);

//    printf("//*Inverted List*//\n");
//    showDLList(invertedList);
    
    // Write the data to invertedIndex.txt
    writeinvertedIndex(invertedList);
    
    // free
    for (int n =0; n < numberOfVertices; n++){
        free(urls[n]);
    }
    
    freeDLList(collectionUrls);
    freeDLList(invertedList);

}

