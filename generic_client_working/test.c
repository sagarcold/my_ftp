#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char*stream = (char*)malloc(100);
	int ch;
	FILE *fp;
	printf("Enter the file name to display its contents\n");
	fgets(stream,100,stdin);
	*(stream+strlen(stream)-1)='\0';
	printf("%s\n",stream);
	__fpurge(stdout);
	if(fp = fopen(stream,"r"))
	/*{
		printf("FIle cannot be opend..!!\n");
		exit(1);
	}*/
//	__fpurge(stdin);
	
{	printf("opend file\n");
	while((ch=fgetc(fp))!=EOF)
	{
		printf("%c",ch);
              

	}}
	else
	{
		printf("Cannot open file..!!\n");
		exit(1);
	}
	printf("\n");
	fclose(fp);
	return 0;

}
