#include "DLListSearch.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE 1000
#define FAIL "Fail to read!"

void bubble_sort(float pagerank[], int len, int printNum[]);

int main(int argc, char *argv[]) {
    // check params have passed
    char line[MAX_LINE];
    char pagerankListdelim[3] = " ,", invertedIndexdelim[3] = " ,";
    FILE *fp;
    char *token;
    int count, numberOfDegrees = 0;
    char url[MAX_LINE], word[MAX_LINE];
    double rankValue = 0.0;
    DLList pageRankList, invertedList;
    
    // check if the params are available
    if (argc > 1) {
        DLList paramsList = newDLList(), pageRankList = newDLList(), invertedList = newDLList();
        for (int i = 1; i < argc; i++) {
            addDLList(paramsList, argv[i], 0, 0.0);
        }

        // read pagerankList.txt
        if ((fp = fopen("pagerankList.txt", "r")) == NULL){
                    perror("FAIL");
                    exit(1);
                } else {
                    while (fgets(line, MAX_LINE, fp) != NULL) {
                        line[strlen(line) - 1] = '\0';
                        count = 0;
                        token = strtok(line, pagerankListdelim);

                        do {
                            if (count == 0) {
                                strcpy(url, token);
                                url[strlen(token)] = '\0';
                            } if (count == 1) {
                                numberOfDegrees = atoi(token);    // make string to integer 
                            } if (count == 2) {
                                rankValue = atof(token);
                            }
                            token = strtok(NULL, pagerankListdelim);
                            count ++;                     
                        } while (token != NULL);
        
                    addDLList(pageRankList, url, numberOfDegrees, rankValue);
                }
                fclose(fp);
        }
        
        // read invertedIndex.txt
        if ((fp = fopen("invertedIndex.txt", "r")) != NULL) {
                while (fgets(line, MAX_LINE, fp) != NULL) {
                    // delete \n
                    line[strlen(line) - 1] = '\0';        
                    count = 0;
                    token = strtok(line, invertedIndexdelim);
                    while (token != NULL) {
                        if (count == 0) {
                            strcpy(word, token);
                            word[strlen(token)] = '\0';
                        } else {
                            // insert page rank
                            addDLListAndChild(invertedList, word, token);
                        }
                        // continue to get string
                        token = strtok(NULL, invertedIndexdelim);
                        count++;
                    }        
                }
                fclose(fp);
            }  
        
        // showDLList(invertedList);
        
        DLList searchResult = newDLList();
        
        searchInvertedDLList(paramsList, pageRankList, invertedList, searchResult);
        
        int numofurls = lengthDLList(pageRankList);
        float pagerank[numofurls];
        int printNum[numofurls];
        
        copyPagerank(pageRankList, pagerank);
        
        for (int n =0; n < numofurls; n++){
            printNum[n] = numofurls - n;
            
        }
        
        bubble_sort(pagerank, numofurls, printNum);
        
//        printUrl(pageRankList, printNum);

        // Free all of them
        freeDLList(paramsList);
        freeDLList(invertedList);
        freeDLList(pageRankList);
    }
}

void bubble_sort(float pagerank[], int len, int printNum[]) {
    int i, j, temp;
    float ftemp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (pagerank[j] > pagerank[j + 1]) {
                ftemp = pagerank[j];
                pagerank[j] = pagerank[j + 1];
                pagerank[j + 1] = ftemp;
                temp = printNum[j];
                printNum[j] = printNum[j + 1];
                printNum[j + 1] = temp;
            }
}