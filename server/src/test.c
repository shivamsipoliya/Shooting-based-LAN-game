#include<stdio.h>
main()
{
	FILE* fp =fopen("map2.txt","r");
	int i,j;
	while(fscanf(fp,"%d %d",&i,&j)!=EOF)
	{
		printf("%d %d\n",i,j);
	}
	
}


