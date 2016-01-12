#include "./../include/Objects.h"

//GENERATES THE PLAYERID FOR COMMANDO

extern int generate_player_id;

//SETS RANDOM POSITION OF THE COMMANDOON MAP

void SetCommando(PositionType map_matrix[ROWS][COLUMNS],Commando * com)
{
		while(1)
		{
			(*com).i=rand()%ROWS;
			(*com).j=rand()%COLUMNS;
			if(map_matrix[(*com).i][(*com).j]==NONE)
			{
				map_matrix[(*com).i][(*com).j]=BOOKED;
				break;
			}
		}
		(*com).dir=DOWN;
		(*com).energy=100;
		(*com).score=0;
		generate_player_id++;
		(*com).pid=generate_player_id;
		strcpy((*com).name,"AutoCommando");
}
