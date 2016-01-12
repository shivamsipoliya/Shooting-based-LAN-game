
#include "./../include/Objects.h"
int generate_player_id=0;

//SETS THE POSITION OF APPLE RANDOMLY

void SetApple(PositionType map_matrix[ROWS][COLUMNS],Apple* app)
{
	
	while(1)
	{
		(*app).i=rand()%ROWS;
		(*app).j=rand()%COLUMNS;
		if(map_matrix[(*app).i][(*app).j]==NONE)
		{
			map_matrix[(*app).i][(*app).j]=BOOKED;
			break;
		}
	}
}


