extern int timercount=0;
extern int max_players;
extern int auto_commando_count;
extern int auto_alien_count;
Server_struct server_data;


using namespace std;
void spaceEvent(unsigned char key, int pid, int)
{

	if(key == ' ')
	{
       if(getCommandoIndex(pid)!=-1)  
       	{int  pos=getCommandoIndex(pid);
       	Bullet b;
		b.i = server_data.commandos[pos].i;
		b.j = server_data.commandos[pos].j;
		b.dir=server_data.commandos[pos].dir;
		b.pid=pid;
		addBullet(b);
       }
       else if(getAlienIndex(pid)!=-1)
       {int  pos=getAlienIndex(pid);
       	Bullet b;
		b.i = server_data.aliens[pos].i;
		b.j = server_data.aliens[pos].j;
		b.dir=server_data.aliens[pos].dir;
		b.pid=pid;
		addBullet(b);
       }
	else if(key==27)exit(0);
    //glutPostRedisplay();*/
}
}
int getAlienIndex(int pid)
{
   int i=0;
	for(i;i<server_data.alien_count;i++)
	{
		if(server_data.aliens[i].pid==pid)
			return i;
			
	}
	return -1;
}

int getCommandoIndex(int pid)
{
   int i=0;
	for(i;i<server_data.commando_count;i++)
	{
		if(server_data.commandos[i].pid==pid)
			return i;
			
	}
	return -1;
}


void keyEvent(int key, int pid, int)
{
     int nexti,nextj;
	int pos;
	 if(getCommandoIndex(pid)!=-1)  
       	{int  pos=getCommandoIndex(pid);
       	
	
	nexti=server_data.commandos[pos].i;
	nextj=server_data.commandos[pos].j;
   
    switch (key)
    {
	
    case GLUT_KEY_DOWN:
	if(server_data.commandos[pos].dir!=DOWN)server_data.commandos[pos].dir=DOWN;
	else if(server_data.commandos[pos].i>0)
		nexti--;
        break;
    case GLUT_KEY_UP:
	 if(server_data.commandos[pos].dir!=UP)server_data.commandos[pos].dir=UP;
	else if(server_data.commandos[pos].i<(ROWS-1))
		nexti++;		
        break;
    case GLUT_KEY_LEFT:
	if(server_data.commandos[pos].dir!=LEFT)server_data.commandos[pos].dir=LEFT;
	else if(server_data.commandos[pos].j>0)
		nextj--;
	break;
    case GLUT_KEY_RIGHT:
        if(server_data.commandos[pos].dir!=RIGHT)server_data.commandos[pos].dir=RIGHT;
	else if(server_data.commandos[pos].j<(COLUMNS-1))
		nextj++;
	break;
	
    }
    if(CheckPlayerCollide(nexti,nextj)== -1 && isObstacle(nexti,nextj)==0 &&checkCommandoCollide(nexti,nextj)== -1 )
    {
	if(checkAppleCollide(nexti,nextj)!=-1)
	{
		server_data.map_matrix[server_data.commandos[pos].i][server_data.commandos[pos].j]=NONE;
		int pos_app=checkAppleCollide(nexti,nextj);
		destroyGenerateApple(pos_app);
		if(server_data.commandos[pos].energy <= 100 && server_data.commandos[pos].energy >= 80) {server_data.commandos[pos].energy =100;}
		else if(server_data.commandos[pos].energy < 80){
		server_data.commandos[pos].energy+=20;
		}
		server_data.commandos[pos].score+=100;
		server_data.commandos[pos].i=nexti;
		server_data.commandos[pos].j=nextj;
		server_data.map_matrix[nexti][nextj]=BOOKED;
	}
        else if(checkBulletCollide(nexti,nextj)!=-1)
	{
           	
  
		server_data.map_matrix[server_data.commandos[pos].i][server_data.commandos[pos].j]=NONE;
		server_data.commandos[pos].energy-=25;
		
		int bulletpos =checkBulletCollide(nexti,nextj);
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
		
		
		if(server_data.commandos[pos].energy <0)
		   deleteCommando(pos);
		   
		int pos_bul=checkBulletCollide(nexti,nextj);
		deleteBullet(pos_bul);
	}
	else
	{
		//server_data.map_matrix[server_data.commandos[pos].i][server_data.commandos[pos].j]=NONE;
		server_data.commandos[pos].i=nexti;
		server_data.commandos[pos].j=nextj;
		server_data.map_matrix[server_data.commandos[pos].i][server_data.commandos[pos].j]=BOOKED;
	}
    }
    	}
    	
    	
    	//Alien 
    	else if(getAlienIndex(pid)!=-1)  
       	{int  pos=getAlienIndex(pid);
       	
	
	nexti=server_data.aliens[pos].i;
	nextj=server_data.aliens[pos].j;
   
    switch (key)
    {
	
    case GLUT_KEY_DOWN:
	if(server_data.aliens[pos].dir!=DOWN)server_data.aliens[pos].dir=DOWN;
	else if(server_data.aliens[pos].i>0)
		nexti--;
        break;
    case GLUT_KEY_UP:
	 if(server_data.aliens[pos].dir!=UP)server_data.aliens[pos].dir=UP;
	else if(server_data.aliens[pos].i<(ROWS-1))
		nexti++;		
        break;
    case GLUT_KEY_LEFT:
	if(server_data.aliens[pos].dir!=LEFT)server_data.aliens[pos].dir=LEFT;
	else if(server_data.aliens[pos].j>0)
		nextj--;
	break;
    case GLUT_KEY_RIGHT:
        if(server_data.aliens[pos].dir!=RIGHT)server_data.aliens[pos].dir=RIGHT;
	else if(server_data.aliens[pos].j<(COLUMNS-1))
		nextj++;
	break;
	
    }
    if(CheckPlayerCollide(nexti,nextj)== -1 && isObstacle(nexti,nextj)==0 &&checkCommandoCollide(nexti,nextj)== -1 )
    {
	if(checkAppleCollide(nexti,nextj)!=-1)
	{
		
	}
        else if(checkBulletCollide(nexti,nextj)!=-1)
	{
		server_data.map_matrix[server_data.aliens[pos].i][server_data.aliens[pos].j]=NONE;
		server_data.aliens[pos].energy-=20;
		
		
		int bulletpos =checkBulletCollide(nexti,nextj);
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
		
		
		if(server_data.aliens[pos].energy<0)
			deleteAlien(pos);
		int pos_bul=checkBulletCollide(nexti,nextj);
		deleteBullet(pos_bul);
	}
	else
	{
		//server_data.map_matrix[server_data.aliens[pos].i][server_data.aliens[pos].j]=NONE;
		server_data.aliens[pos].i=nexti;
		server_data.aliens[pos].j=nextj;
		server_data.map_matrix[server_data.aliens[pos].i][server_data.aliens[pos].j]=BOOKED;
	}
 }
  
}
}


void timer(int = 0)
{

  while(1){
  
   timercount++;
  moveAutoPlayers();
 
   displayAllBullets();
   send_to_all();
   usleep(150000);
}
}

// CLEARS THE SCREEN

void clrScreen()
{
	system("clear");
	printf("\n\n\n\n\n\n");
	
}

//PRINTS TEXT AT THE CENTER
void printCenter(char * p)
{
	for(int i=0;i<20;i++)printf(" ");
	printf("%s",p);
}

float r1=0,g1=0,b1=1,r2=0,g2=0,b2=1,r3=0,g3=0,b3=1;



