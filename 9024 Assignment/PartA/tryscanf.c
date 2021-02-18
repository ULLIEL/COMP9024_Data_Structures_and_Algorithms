#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024

int main()
{
	char buf[MAX_LINE];  /*缓冲区*/
	FILE *fp;            /*文件指针*/
	int len;             /*行字符个数*/
	char *tranverse;
	int N = 0;	
	
	if ((fp = fopen("collection.txt","r")) != NULL){
		while (fgets(buf,MAX_LINE,fp) != NULL) {
			
		len = strlen(buf);  
		// the function of strlen() is deleting '\0' of string
		buf[len-1] = '\0';  
		fscanf(fp, "%s ", buf);
		printf("%s\n", buf);
		}

	}
}