/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "header.h"

//This is received when player joins the game.
struct playerinfo
{
	char name[50];
	PlayerType player_type; 
};

typedef playerinfo Playerinfo;

//Receiving structure
struct recv_client_struct
{
	int pid;
	PlayerType player_type;
	char key; 
};
typedef struct recv_client_struct Recv_client_struct;

//Server will send this data to every client whenever an action is taken place.
struct server_struct
{
	Bullet bullets[20];
	Alien aliens[5];
	int bullet_count;
	int alien_count;
	int apple_count;
	int commando_count;
	Commando commandos[5];
	Apple apples[5];
	PositionType map_matrix[ROWS][COLUMNS];
} ;


typedef struct server_struct Server_struct;


//Functions Used

void error(const char *msg);
char* GetPlayerType(PlayerType p);
void serverInit(int portno);
int joinPlayer(char name[25],PlayerType player_type);
void receiveIncomingConnections();
void client(void *ptr);
void shutDownServer();
void send_to_all();
void showAllData(int flag); 


