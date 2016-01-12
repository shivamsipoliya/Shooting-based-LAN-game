#include "./../include/header.h"
#include "./../include/Objects.h"
#include "./../include/ServerNetwork.h"
#include "./../include/ServerMain.h"

//int timercount;
int max_players;
int auto_commando_count;
int auto_alien_count;
extern Server_struct server_data;

//INITIALIZES THE GAME

void initializeGame(int map_id)
{
	int i,j;
	PositionType t;
	char map_name[15];
	sprintf(map_name,"maps/map%d.txt",map_id);
	
	//GENERATE MAP MATRIX
	for(i=0;i<ROWS;i++)
	{	
		for(j=0;j<COLUMNS;j++)
		{
			server_data.map_matrix[i][j]=NONE;
		}
	}
	FILE* fp =fopen(map_name,"r");

	//SELECT A MAP FROM VARIOUS AVAILABLE MAP
	if(map_id==1)
	{
		t=PTREE;
	}
	else if(map_id==2)
	{
		t=RIVER;
	}
	else if(map_id==3)
	{
		t=MOUNTAIN;
	}
	else if(map_id==4)
	{
		t=CIRCLE;
	}
	else
	{
		t=BOX;
	}
	
	
	while(fscanf(fp,"%d %d",&i,&j)!=EOF)
	{
		
		server_data.map_matrix[i][j]=t;
	}
	
	for(i=1;i<COLUMNS-1;i+=2)
	{
		server_data.map_matrix[0][i]=PTREE;
		
	}
	
	for(i=1;i<COLUMNS-1;i+=2)
	{
		server_data.map_matrix[ROWS-1][i]=PTREE;
	}
	
	server_data.commando_count=0;
	server_data.alien_count=0;
	server_data.bullet_count=0;
	server_data.apple_count=0;
	
	for(int i=0;i<auto_alien_count;i++)
	{
		Alien alien;
		alien.isauto=1;
		SetAlien(server_data.map_matrix,&alien);
		server_data.aliens[server_data.alien_count]=alien;
		server_data.alien_count++;
		
	}
	for(int i=0;i<auto_commando_count;i++)
	{
		Commando commando;
		commando.isauto=1;
		SetCommando(server_data.map_matrix,&commando);
		server_data.commandos[server_data.commando_count]=commando;
		server_data.commando_count++;
	}
	for(int i=0;i<5;i++)
	{
		Apple apple;
		SetApple(server_data.map_matrix,&apple);
		server_data.apples[server_data.apple_count]=apple;
		server_data.apple_count++;
		
	}
}

//ADD ALIEN TO MAP

void addAlien(Alien alien)
{
	if(server_data.alien_count<10){
	server_data.aliens[server_data.alien_count]=alien;
	server_data.alien_count++;
	}
}

//ADD BULLET TO MAP

void addBullet(Bullet bullet)
{
	if(server_data.bullet_count<10){
	server_data.bullets[server_data.bullet_count]=bullet;
	server_data.bullet_count++;
	}
}

//ADD COMMANDO TO MAP

void addCommando(Commando commando)
{
	if(server_data.commando_count<10){
	server_data.commandos[server_data.commando_count]=commando;
	server_data.commando_count++;
	}
}

//ADD APPLE TO MAP

void addApple(Apple apple)
{
	if(server_data.apple_count<10){
	server_data.apples[server_data.apple_count]=apple;
	server_data.apple_count++;
	}
}

//DELETE APPLE FROM MAP 

void deleteApple(int i)
{
 	
	if(i== server_data.apple_count-1);
	 if(i >=0 && i< server_data.apple_count){
	for(int pos =i+1;pos<server_data.apple_count;pos++){
	server_data.apples[pos-1]=server_data.apples[pos];
	}
	}
	server_data.apple_count--;
	
}
//DELETE THE BULLET FROM MAP

void deleteBullet(int i)
{
	if(i==server_data.bullet_count-1);
	else if(i >=0 && i< server_data.bullet_count){
	for(int pos =i+1;pos<server_data.bullet_count;pos++){
	server_data.bullets[pos-1]=server_data.bullets[pos];
	
	}
	
	
	}
	server_data.bullet_count--;
}

//DELETE THE COMMAND FROM MAP

void deleteCommando(int i)
{

	if(i==server_data.commando_count-1);
	else if(i >=0 && i< server_data.commando_count){
	for(int pos =i+1;pos<server_data.commando_count;pos++){
	server_data.commandos[pos-1]=server_data.commandos[pos];
	
	}
	
	}server_data.commando_count--;
	
}
	
//DELETE THE ALIEN FROM MAP

	void deleteAlien(int i)
{

	if(i==server_data.alien_count-1);
	else if(i >=0 && i< server_data.alien_count){
	for(int pos =i+1;pos<server_data.alien_count;pos++){
	server_data.aliens[pos-1]=server_data.aliens[pos];
	
	}
	
	}server_data.alien_count--;
	
}
