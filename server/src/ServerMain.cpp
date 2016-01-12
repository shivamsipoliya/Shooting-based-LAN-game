#include <GL/glut.h>
#include <GL/gl.h>
#include "./../include/ServerMain.h"
#include<GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <math.h>
#include <bitset>
#include <vector>
#include "./../include/Objects.h"
#include "./../include/ServerNetwork.h"
#include "./../include/Map.h"
#include "ServerLogic.cpp"
//CHANGE IN MAIN

int main(int argc, char *argv[])
{
	int portno,map_id;
	pthread_t receive_connection_thread;
	int receive_t;
	portno=atoi(argv[1]);
	char usertext[10];
	system("setterm -term linux -back green -fore white -bold on -clear");		
	//system("gnome-terminal ");
	//gotoxy(50,50);
	fflush(stdout);	
	clrScreen();
	printCenter("Max No. of Players : ");
	scanf("%d",&max_players);
	clrScreen();
	printCenter("No. Of Automatic Commandos : ");
	scanf("%d",&auto_commando_count);
	clrScreen();	
	printCenter("No.Of Automatic ALiens : ");
	scanf("%d",&auto_alien_count);
	printCenter("   Choose Arena\n");
	printCenter("******************\n");
	printCenter("1 : Forest_War\n");
	printCenter("2 : Nuke_Alien\n");
	printCenter("3 : Mountain_Comm\n");
	printCenter("4 : Mission_Earth\n");
	printCenter("5 : Collapse_CA\n");
	printCenter("Your Choice : ");
	scanf("%d",&map_id);
	clrScreen();	
	initializeGame(map_id);
	serverInit(portno);
	printCenter(" *********The Game Begins Now*******\n");
	printCenter("          Server Established \n");
	printCenter("Waiting For Incomming Connections...\n");
	
	
	//timer();
	//change
	pthread_create(&receive_connection_thread,NULL,receiveIncomingConnections,(void *)&receive_t);
	
	//receiveIncomingConnections();   
	while(1)
	
	{
		printCenter("Press x to Shutdown Server : ");
		scanf("%s",usertext);
		if(strcmp(usertext,"q")==0)
		{
			
			
			system("setterm -default");
	          system("clear");
	   
	           printf("All Connections Terminated\n");
			printf("Server ShutDown\n");
			showAllData(-1);
			shutDownServer();
			//exit(0);
			
		}
		else
		{
			printCenter("Please enter x to quit :\n");
		}
	}
}

void displayAllBullets()
{
	int pos;
	for (int i=0;i<server_data.bullet_count;i++)
        {   

		Bullet b=server_data.bullets[i];
	        switch(b.dir)
		{
			case DOWN:
				b.i = b.i-1;
				break;
			case UP:
				b.i = b.i+1;
				break;
			case RIGHT:
				b.j = b.j+1;
				break;
			case LEFT:
				b.j = b.j-1;
				break;
		}
		if(CheckPlayerCollide(b.i,b.j)!=-1)
		{      
		
		     pos=CheckPlayerCollide(b.i,b.j);
			deleteBullet(i);
			Alien a=server_data.aliens[pos];
			a.energy -=20;	
			server_data.aliens[pos]=a;	
			
		
		if(getCommandoIndex(server_data.bullets[i].pid)!=-1)
		{
			int commpos =getCommandoIndex(server_data.bullets[i].pid);
			 server_data.commandos[commpos].score +=100; 
			
		}
		if(getAlienIndex(server_data.bullets[i].pid)!=-1)
		{
			int alienpos =getAlienIndex(server_data.bullets[i].pid);
			 server_data.aliens[alienpos].score -=100; 
			
		}
			

			if(a.energy <= 0)
			{server_data.map_matrix[a.i][a.j]=NONE;
			deleteAlien(pos);}
		 
				
		}
		else if(checkAppleCollide(b.i,b.j)!=-1)
		{	
			pos=checkAppleCollide(b.i,b.j);

			deleteBullet(i);

			destroyGenerateApple(pos);
			server_data.map_matrix[b.i][b.j]=NONE;
		}
		else if(isObstacle(b.i,b.j))
		{

			deleteBullet(i);
			server_data.map_matrix[b.i][b.j]=NONE;
		}
		else if(checkBulletCollide(b.i,b.j)!=-1)
		{
			pos=checkBulletCollide(b.i,b.j);

			if(i>pos)
			{
			deleteBullet(i);
			deleteBullet(pos);
			}
			else
			{
			deleteBullet(pos);
			deleteBullet(i);
			}
			server_data.map_matrix[b.i][b.j]=NONE;
		}
		if(checkCommandoCollide(b.i,b.j)!=-1)
		{       
		
			pos=checkCommandoCollide(b.i,b.j);
			
			Commando c=server_data.commandos[pos];
			c.energy -=20;	
			server_data.commandos[pos]=c;
			
			
			
		if(getCommandoIndex(server_data.bullets[i].pid)!=-1)
		{
			int commpos =getCommandoIndex(server_data.bullets[i].pid);
			 server_data.commandos[commpos].score -=100; 
			
		}
		if(getAlienIndex(server_data.bullets[i].pid)!=-1)
		{
			int alienpos =getAlienIndex(server_data.bullets[i].pid);
			 server_data.aliens[alienpos].score +=100; 
			
		}
			
   			
			if(c.energy <= 0)
			{server_data.map_matrix[c.i][c.j]=NONE;
			deleteCommando(pos);}
			deleteBullet(i);
		
		}
		else
		{
			server_data.bullets[i]=b;
			if(b.i<0 || b.i>(ROWS-1) ||b.j <0 || b.j >(COLUMNS-1) )
			{
				deleteBullet(i);
			}
		}
	}
}


int CheckPlayerCollide(int i,int j)
{
	for (int pos=0;pos<server_data.alien_count;pos++)
        {   	Alien a=server_data.aliens[pos];
		if(a.i==i&&a.j==j)
		{
			return pos;
		}
	}
	return -1;
}
int checkBulletCollide(int i,int j)
{
	for (int pos=0;pos<server_data.bullet_count;pos++)
        {   
		Bullet b=server_data.bullets[pos];
		if(b.i==i&&b.j==j)
		{
			return pos;
		}
	}		
	return -1;
}
int checkAppleCollide(int i,int j)
{
	for (int pos=0;pos<server_data.apple_count;pos++)
        {   
		Apple a=server_data.apples[pos];
		if(a.i==i&&a.j==j)
		{
			return pos;
		}
	}		
	return -1;
}
int isObstacle(int i,int j)
{
	if(server_data.map_matrix[i][j]==PTREE||server_data.map_matrix[i][j]==RIVER||server_data.map_matrix[i][j]==MOUNTAIN||server_data.map_matrix[i][j]==CIRCLE||server_data.map_matrix[i][j]==BOX)
		return 1;
	else
		return 0;
}

void destroyGenerateApple(int pos)
{
		deleteApple(pos);		
		Apple apple;
		SetApple(server_data.map_matrix,&apple);
		addApple(apple);
			
}

double calculate_distance (double x1,double y1,double x2 ,double y2)
{
	double distance;
	double distance_x = x1-x2;
	double distance_y = y1- y2; 
	distance = sqrt( (distance_x * distance_x) + (distance_y * distance_y));
	return distance;
}
int aliensenserhorizontal(int nearcom , int alienpos)
{
Alien a1=server_data.aliens[alienpos];
Commando c1=server_data.commandos[nearcom];

 for (int pos=0;pos<server_data.alien_count;pos++)
        {   	Alien a=server_data.aliens[pos]; 
        
        		  		
          if(pos != alienpos && a.i ==a1.i && ((a.j> a1.j && a.j < c1.j)|| (a.j < a1.j && a.j > c1.j))  )
                 
		{

					return 1;
		}
	}
	return 0;

}

int aliensenservertical(int nearcom , int alienpos)
{ 
 Alien a1=server_data.aliens[alienpos];
Commando c1=server_data.commandos[nearcom];
 for (int pos=0;pos<server_data.alien_count;pos++)
        {   	Alien a=server_data.aliens[pos];
                 if(pos != alienpos && a.j ==a1.j && ((a.i> a1.i && a.i < c1.i)|| (a.i < a1.i && a.i > c1.i))  )
		{
		     
		     			return 1;
		}
	}
	return 0;

}

int commandosenserhorizontal(int nearal , int compos)
{
Alien c1=server_data.aliens[nearal];
Commando a1=server_data.commandos[compos];

 for (int pos=0;pos<server_data.commando_count;pos++)
        {   	Commando a=server_data.commandos[pos]; 
          if(pos != compos && a.i ==a1.i && ((a.j> a1.j && a.j < c1.j)|| (a.j < a1.j && a.j > c1.j))  )
                 
		{
		  					return 1;
		}
	}
	return 0;

}

int commandosenservertical(int nearal , int compos)
{
Alien c1=server_data.aliens[nearal];
Commando a1=server_data.commandos[compos];

 for (int pos=0;pos<server_data.commando_count;pos++)
        {   	Commando a=server_data.commandos[pos]; 
          if(pos != compos && a.j ==a1.j && ((a.i> a1.i && a.i < c1.i)|| (a.i < a1.i && a.i > c1.i))  )
                 
		{
		  
					return 1;
		}
	}
	return 0;

}
void moveAutoPlayers()
{
  int key;
	for (int i=0;i<server_data.alien_count;i++)
        { 
        	if(server_data.aliens[i].isauto)
          {		   
		int nearerpos;
		Alien a=server_data.aliens[i];
		int pos;
		
		int previ=a.i,prevj=a.j;
		
		if(server_data.commando_count ==0) break;

  	int min=0;;	
	    for(int pos=0;pos<server_data.commando_count;pos++)
	{
				
		nearerpos=0;
		if(min>calculate_distance(a.i,a.j,server_data.commandos[pos].i,server_data.commandos[pos].j))			
		{min=calculate_distance(a.i,a.j,server_data.commandos[pos].i,server_data.commandos[pos].j); nearerpos=pos;}

	}


		if(timercount%5==0)
		{
		if(a.i > server_data.commandos[nearerpos].i) {key =0;}
		else if(a.i < server_data.commandos[nearerpos].i) {key =1;} 
		else if(a.j < server_data.commandos[nearerpos].j) {key=3;
		}
		else if(a.j > server_data.commandos[nearerpos].j) {key=2;
					
		}
		 
		switch (key)
    		{
	
    			case 0:
				if(a.dir!=DOWN)a.dir=DOWN;
				else if(a.i>0)
				a.i--;
        			break;
			    case 1:
				if(a.dir!=UP)a.dir=UP;
				else if(a.i<(ROWS-1))
					a.i++;		
				break;
			    case 2:
				if(a.dir!=LEFT)a.dir=LEFT;
				else if(a.j>0)
					a.j--;
				
				break;
			    case 3:
				if(a.dir!=RIGHT)a.dir=RIGHT;
				else if(a.j<(COLUMNS-1))
					a.j++;
				break;
	
			 
    		}
		
		
		
		 if(!(isObstacle(a.i,a.j)))
    		{
			if(checkAppleCollide(a.i,a.j)!=-1)
			{
				Bullet b;
	 			b.i = previ;
				b.j = prevj;
				b.dir=a.dir;
				b.pid=a.pid;
				addBullet(b);
				
			}
			else if(checkBulletCollide(a.i,a.j)!=-1)
			{
				a.energy -=20;
				
		int bulletpos =checkBulletCollide(a.i,a.j);
		if(getCommandoIndex(server_data.bullets[bulletpos].pid)!=-1)
		{
			int commpos =getCommandoIndex(server_data.bullets[bulletpos].pid);
			 server_data.commandos[commpos].score +=100; 
			
		}
		if(getAlienIndex(server_data.bullets[bulletpos].pid)!=-1)
		{
			int alienpos =getAlienIndex(server_data.bullets[bulletpos].pid);
			 server_data.aliens[alienpos].score -=100; 
			
		}
				
			        if(a.energy <=0)
				{server_data.map_matrix[a.i][a.j]=NONE;}
			}
			else if(CheckPlayerCollide(a.i,a.j)!=-1 && CheckPlayerCollide(a.i,a.j) !=i)
				{       
					
				}
			else
			{
				if(checkCommandoCollide(a.i,a.j)==-1)
				{
				//server_data.map_matrix[previ][prevj]=NONE;
				server_data.map_matrix[a.i][a.j]=BOOKED;
				a.energy -=1;
				server_data.aliens[i]=a;}
				else
				{Bullet b;
	 			b.i = previ;
				b.j = prevj;
				b.dir=a.dir;
				b.pid=a.pid;
				addBullet(b);
				}
			}
			
    		}
    		else
		{		Bullet b;
	 			b.i = previ;
				b.j = prevj;
				b.dir=a.dir;
				b.pid=a.pid;
				addBullet(b);	}
		
		if(a.energy <= 0)
		{deleteAlien(i);}
		
    
				
		if(((key == 2 || key ==3 ) && (!aliensenserhorizontal(nearerpos,i)) )|| (prevj = server_data.commandos[nearerpos].j) && (!aliensenservertical(nearerpos,i)) )  {
		Bullet b;
	 	b.i = a.i;
		b.j = a.j;
		b.dir=a.dir;
		b.pid=a.pid;
		addBullet(b);	}
			
		}
		
      }
      }
      
      for (int i=0;i<server_data.commando_count;i++)
        { 
        
        
        if(server_data.commandos[i].isauto)
          {
        	
		int nearerpos;
		Commando a=server_data.commandos[i];
		int pos;
		int previ=a.i,prevj=a.j;
		
	
 	if(server_data.alien_count ==0) break;
  	 int min=0;
  	 
	    for(int pos=0;pos<server_data.alien_count;pos++)
	{
				
		nearerpos=0;
		if(min>calculate_distance(a.i,a.j,server_data.aliens[pos].i,server_data.aliens[pos].j))			
		{min=calculate_distance(a.i,a.j,server_data.aliens[pos].i,server_data.aliens[pos].j); nearerpos=pos;}

	}
 

		if(timercount%5==0)
		{
		if(a.i > server_data.aliens[nearerpos].i) {key =0;}
		else if(a.i < server_data.aliens[nearerpos].i) {key =1;} 
		else if(a.j < server_data.aliens[nearerpos].j) {key=3;
		}
		else if(a.j > server_data.aliens[nearerpos].j) {key=2;
					
		}
		 
		switch (key)
    		{
	
    			case 0:
				if(a.dir!=DOWN)a.dir=DOWN;
				else if(a.i>0)
				a.i--;
        			break;
			    case 1:
				if(a.dir!=UP)a.dir=UP;
				else if(a.i<(ROWS-1))
					a.i++;		
				break;
			    case 2:
				if(a.dir!=LEFT)a.dir=LEFT;
				else if(a.j>0)
					a.j--;
				
				break;
			    case 3:
				if(a.dir!=RIGHT)a.dir=RIGHT;
				else if(a.j<(COLUMNS-1))
					a.j++;
				break;
	
			 
    		}
		
		
		
		 if(!(isObstacle(a.i,a.j)))
    		{
			if(checkAppleCollide(a.i,a.j)!=-1)
			{
				
				
				server_data.map_matrix[server_data.commandos[i].i][server_data.commandos[i].j]=NONE;
		int pos_app=checkAppleCollide(a.i,a.j);
		destroyGenerateApple(pos_app);
		if(server_data.commandos[i].energy <= 100 && server_data.commandos[i].energy >= 80) {server_data.commandos[i].energy =100;}
		else if(server_data.commandos[i].energy < 80){
		server_data.commandos[i].energy+=20;
		}
		server_data.commandos[i].score+=100;
		server_data.commandos[i].i=a.i;
		server_data.commandos[i].j=a.j;
		server_data.map_matrix[a.i][a.j]=BOOKED;
		server_data.commandos[i]=a;
		
		
		
		
		
				
			}
			else if(checkBulletCollide(a.i,a.j)!=-1)
			{
				
				a.energy -=25;
				
		int bulletpos =checkBulletCollide(a.i,a.j);
		if(getCommandoIndex(server_data.bullets[bulletpos].pid)!=-1)
		{
			int commpos =getCommandoIndex(server_data.bullets[bulletpos].pid);
			 server_data.commandos[commpos].score -=100; 
			
		}
		if(getAlienIndex(server_data.bullets[bulletpos].pid)!=-1)
		{
			int alienpos =getAlienIndex(server_data.bullets[bulletpos].pid);
			 server_data.aliens[alienpos].score +=100; 
			
		}
				
			      if(a.energy <=0)
				{
				
				server_data.map_matrix[a.i][a.j]=NONE;}
				
						
				
			}
			else if(checkCommandoCollide(a.i,a.j)!=-1 && checkCommandoCollide(a.i,a.j) !=i)
				{       
					
					
				}
			else
			{
				
				if(CheckPlayerCollide(a.i,a.j)==-1)
				{
			//	server_data.map_matrix[previ][prevj]=NONE;
				server_data.map_matrix[a.i][a.j]=BOOKED;
				server_data.commandos[i]=a;
									
				}
				
				else
				{Bullet b;
	 			b.i = previ;
				b.j = prevj;
				b.dir=a.dir;
				b.pid=a.pid;
				addBullet(b);
				
				}
				
										
			}
    		}
    		else{Bullet b;
	 	b.i = previ;
		b.j = prevj;
		b.dir=a.dir;
		b.pid=a.pid;
		addBullet(b);
		}
		
		if(a.energy <= 0)
		{deleteCommando(i);}
		
		
	//	printf("asfasfasdfas*****  %d \n  ",aliensenserhorizontal(nearerpos,i)));
				
		
		if(((key == 2 || key ==3 ) && (!commandosenserhorizontal(nearerpos,i)) )|| (a.j == server_data.aliens[nearerpos].j) && (!commandosenservertical(nearerpos,i)) )  {
		
		Bullet b;
	 	b.i = a.i;
		b.j = a.j;
		b.dir=a.dir;
		b.pid=a.pid;
		addBullet(b);}
			
		}
		
      }
      
     } 
      
      
      
	
	
}

int checkCommandoCollide(int i,int j)
{
	for(int pos=0;pos<server_data.commando_count;pos++)
	{
		if(server_data.commandos[pos].i==i&&server_data.commandos[pos].j==j)
		{
			return pos;
		}
	}
	return -1;
}


