#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

void ReadCollection();

int main()
{
	ReadCollection();
}

void ReadCollection(){
	char buf[MAX_LINE];  /*缓冲区*/
	FILE *fp;            /*文件指针*/
	int len;             /*行字符个数*/
	char *tranverse;
	int N = 0;	
		
	if((fp = fopen("collection.txt","r")) == NULL){
		perror("fail to read");
		exit (1);
	} else {
		while(fscanf(fp, "%s", buf) != EOF){
			printf("%s \n",buf);
			
		}		
	
	}
	
}
