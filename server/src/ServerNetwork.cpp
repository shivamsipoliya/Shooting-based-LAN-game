#include "./../include/header.h"
#include "./../include/Objects.h"
#include "./../include/ServerNetwork.h"
#include "./../include/ServerMain.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include<GL/freeglut.h>
#include "./../include/Map.h"

int clients_sockfd[20],server_sockfd;
struct sockaddr_in server_addr, client_addr[20];
int client_index =0,portno;
socklen_t client_length[20];
pthread_t client_threads[20];
pthread_t timer_thread;
int itimer;

int client_isalive[20]={0};
int ic[20];
int timer_flag=0;
int game_start_flag=0;
extern int timercount;
extern int max_players;
extern int auto_commando_count;
extern int auto_alien_count;
extern Server_struct server_data;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

char* GetPlayerType(PlayerType p)
{
	if(p==AL)return "Alien";
	else return "Commando";
}

//INITIALZES THE SERVER BY RESERING PORT

void serverInit(int portno)
{
	server_sockfd =  socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd < 0) 
        error("ERROR opening socket");
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;  //server byte order
	server_addr.sin_addr.s_addr = INADDR_ANY;  //automatically fill with IP
	server_addr.sin_port = htons(portno);
	if (bind(server_sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
     	error("ERROR on binding");
	listen(server_sockfd,20);
}

//JOIN PLAYER WITH TYPE
int joinPlayer(char name[25],PlayerType player_type)
{
	if((server_data.commando_count+server_data.alien_count)>max_players)
	{
		printf("Players limit exceeded You cant connect!!\n");
		return 0;
	}	
	if(player_type==AL)
	{
		Alien alien;
		SetAlien(server_data.map_matrix,&alien);
		strcpy(alien.name,name);
		alien.isauto=0;
		addAlien(alien);
		//if(timer_flag == 0){timer_flag =1;pthread_create(&timer_thread,NULL,timer,(void *)&itimer); }
		printf("%s Joined as Alien\n",name);
		return alien.pid;
	}
	else if(player_type==COM)
	{
		Commando  commando;
		SetCommando(server_data.map_matrix,&commando);
		commando.isauto=0;
		strcpy(commando.name,name);
		addCommando(commando);
		//		if(timer_flag == 0){timer_flag =1;pthread_create(&timer_thread,NULL,timer,(void *)&itimer); }
		printf("%s Joined as Commando\n",name);
		return commando.pid;
	}
}


void receiveIncomingConnections()
{
	int n;
	Playerinfo pinfo;
	while(1)
	{
	     client_length[client_index] = sizeof(client_addr[client_index]);
	     clients_sockfd[client_index] = accept(server_sockfd,(struct sockaddr *) &client_addr[client_index], &client_length[client_index]);
	     if (clients_sockfd[client_index] < 0) 
		{
		  error("ERROR on accept");
		}
	     else
		{   
			ic[client_index]=client_index+1;
			client_isalive[client_index]=1;
			n = recv(clients_sockfd[client_index],&pinfo,sizeof(pinfo),0);
			int pid=joinPlayer(pinfo.name,pinfo.player_type);
			send(clients_sockfd[client_index],&pid,sizeof(pid),0);
			if(pid!=0)
			{
				if(game_start_flag==1)
				{
					printf("Flag Already 1\n");
					n=send(clients_sockfd[client_index],&server_data,sizeof(server_data),0);
		    			pthread_create(&client_threads[client_index],NULL,client,(void *)&ic[client_index]);client_index++;
		    		}
		    		else if((server_data.commando_count>0)&&(server_data.alien_count>0))
		    		{
		    			send_to_all();
		    			game_start_flag=1;    			
		    			n=send(clients_sockfd[client_index],&server_data,sizeof(server_data),0);
		    			
		    			pthread_create(&client_threads[client_index],NULL,client,(void *)&ic[client_index]);client_index++;
		    			pthread_create(&timer_thread,NULL,timer,(void *)&itimer);	
		    		}
		    		else
		    		{
		    			pthread_create(&client_threads[client_index],NULL,client,(void *)&ic[client_index]);client_index++;
		    			
		    		}
		    	}
		    	else
		    	{
		    		close(clients_sockfd[client_index]);
		    	}
		}
  	}
}
void showAllData(int flag)
{
	if(flag==-2)
	{
		clrScreen();
		printCenter("");
		printf("ALIEN TEAM DESTROYED THE EARTH\n");
		printCenter("ALIENS SURVIVED IN THE BATTLE\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     energy\n");
		for(int i=0;i<server_data.alien_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.aliens[i].name,server_data.aliens[i].score,server_data.aliens[i].energy);
		}
	}
	else if(flag==-3)
	{
		clrScreen();
		printCenter("");
		printf("COMMANDOS SAVED THE EARTH\n");
		printCenter("COMMANDOS SURVIVED IN THE BATTLE\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     ENERGY\n");
		for(int i=0;i<server_data.commando_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.commandos[i].name,server_data.commandos[i].score,server_data.commandos[i].energy);
		}
	}
	else
	{
		clrScreen();
		printCenter("");
		printCenter("CURRENT STATUS OF THE GAME\n");
		printCenter("------------------------------\n");
		printCenter("TEAM ALIEN \n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     ENERGY\n");
		for(int i=0;i<server_data.alien_count;i++)
		{
			printCenter("");
			printf("%13ls %5ld %6ld\n",server_data.aliens[i].name,server_data.aliens[i].score,server_data.aliens[i].energy);
		}
		printCenter("TEAM ALIEN\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     ENERGY\n");
		for(int i=0;i<server_data.commando_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.commandos[i].name,server_data.commandos[i].score,server_data.commandos[i].energy);
		}
	}
	printCenter("");
	
}
void client(void *ptr)
{
	
	Recv_client_struct client_data, old_client_data;
	int i,n;
	i=*(int *)ptr;
	
	while(client_isalive[i-1])
	{
		old_client_data=client_data;
	     n = recv(clients_sockfd[i-1],&client_data,sizeof(client_data),0);
	     if (n < 0)
	     {
	     	 error("No message");
	     	 client_isalive[i-1]=0;
	     	 printf("Player with Id %d left the game\n",old_client_data.pid);
	     	 close(clients_sockfd[i-1]);
	     	 return;
	    	}
	    	
	     switch(client_data.key)
	     {
	     	case -2 : showAllData(-2);shutDownServer();break;
	     	case -3 : showAllData(-3);shutDownServer();break;
	     	case -1 : clients_sockfd[i-1]=0;printCenter("");printf("Player with Id %d left the game\n",client_data.pid);break;
	     	case ' ': spaceEvent(client_data.key,client_data.pid,0);break;
	     	case GLUT_KEY_DOWN:keyEvent(client_data.key,client_data.pid,0);break;
	     	case GLUT_KEY_UP:keyEvent(client_data.key,client_data.pid,0);break;
	     	case GLUT_KEY_LEFT:keyEvent(client_data.key,client_data.pid,0);break;
	     	case GLUT_KEY_RIGHT:keyEvent(client_data.key,client_data.pid,0);break;
	     }
	     send_to_all();
		
	 } 
}

void shutDownServer()
{
	for(int i=0;i<client_index;i++)
	{		close(clients_sockfd[i]);
	}
	close(server_sockfd);
	exit(0);
}

void send_to_all()
{
	int k;
	for(int k=0;k<client_index;k++)
			{
				if(client_isalive[k])
				{
					if(send(clients_sockfd[k],&server_data,sizeof(server_data),0)==-1)
					{
						client_isalive[k]=0;
					}
				}
			}
}

