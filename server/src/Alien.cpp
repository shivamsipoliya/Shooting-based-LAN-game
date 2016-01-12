
#include "./../include/Objects.h"

//THIS GENERATES ID FOR THE PLAYER
extern int generate_player_id;

//SETS THE POSITION ON THE MAP
void SetAlien(PositionType map_matrix[ROWS][COLUMNS],Alien *al)
{
	while(1)
	{
		(*al).i=rand()%ROWS;
		(*al).j=rand()%COLUMNS;
		if(map_matrix[(*al).i][(*al).j]==NONE)
		{
			map_matrix[(*al).i][(*al).j]=BOOKED;
			break;
		}
	}
	(*al).dir=DOWN;
	(*al).energy=100;
	(*al).score=0;
	generate_player_id++;
	(*al).pid=generate_player_id;
	strcpy((*al).name,"AutoAlien");
}

