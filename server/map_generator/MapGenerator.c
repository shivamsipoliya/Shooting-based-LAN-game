#include<stdio.h>
main()
{

	int a[13][13];
		int i,j;
	int count=0;	
	for(i=0;i<13;i++)
	{
		for(j=0;j<13;j++)
		{
			a[i][j]=0;
		}
	}
	FILE* fp =fopen("map6.txt","w");
	char ss[5];
	while(count<=50)
	{
		
		i=rand()%13;
		j=rand()%26;
		if(a[i][j]==0)
		{
			sprintf(ss,"%d %d\n", i,j);
			fputs(ss,fp);
			count++;
		}
	}
	fclose(fp);
	
}
