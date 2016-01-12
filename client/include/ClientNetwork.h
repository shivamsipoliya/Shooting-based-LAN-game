//This is received when player joins the game.
#include "header.h"
struct playerinfo
{
	char name[50];
	Ptype player_type; 
};

typedef playerinfo Playerinfo;

//Receiving structure
struct recv_client_struct
{
	int pid;
	Ptype player_type;
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
	PositionType matrix1[ROWS][COLS];
} ;

typedef struct server_struct Server_struct;

//Functions Used
void keepReceivingData();
void error(const char *msg);
int clientInit(int portno, char host[25]);
void keepRePainting();
void showAllData(int flag);
int sendRequest();
//void sendKeyToServer(int key);

