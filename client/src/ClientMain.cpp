#include "./../include/header.h"
#include "./../include/Objects.h"
#include "./../include/ClientMain.h"
#include "./../include/ClientGui.h"
#include "ClientGui.cpp"
#include "./../include/ClientNetwork.h"
#include "ClientNetwork.cpp"

//RETURN THE INDEX OF ALIEN IN LIST IF SUCCESSFULL ELSE RETURN -1
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

//RETURN THE INDEX OF COMMANDO IN LIST IF SUCCESSFULL ELSE RETURN -1
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
//SPACE EVENT HANDLER
void spaceEvent(unsigned char key, int, int)
{
	if(key == ' ')
	{
		sendKeyToServer(key);
     }
	else if(key==27)
	{
		showAllData(-1);
		terminateClient(-5);
		
	}
}

//UP DOWN LEFT RIGHT KEY HANDLER
void keyEvent(int key, int, int)
{
	sendKeyToServer(key);
}

//MOUSE CLICK HANDLER
void fire_mouse()
{
	printf("MOUSE CLICKED");
	sendKeyToServer(' ');
}


int main(int argc, char *argv[])
{
	//INITIALIZE GRAPHICS
	glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800, 800);
     glutInitWindowPosition(0,0);
       glutCreateWindow("ALIAN INVASION");
    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800,800,0,-10,10);
   	if(clientInit(atoi(argv[2]), argv[1])==-1)
	{
		exit(0);
	}
	
	glutDisplayFunc(disp);

 	glutMouseFunc(MouseButton); 
    glutSpecialFunc(keyEvent);
  
    glutKeyboardFunc(spaceEvent);
   	
    glutPassiveMotionFunc(mousedrag);
    
    glutMainLoop();
}
//DRAW ALL BULLETS
void displayAllBullets()
{
	for (int i=0;i<server_data.bullet_count;i++)
     {   
     	Bullet b=server_data.bullets[i];
		drawBullet(b.i,b.j);
	}
}

//DRAW ALL PLAYERS ON THE SCREEN
void displayPlayers()
{
	
	for (int i=0;i<server_data.alien_count;i++)
        {   
		Alien a=server_data.aliens[i];
		if(a.pid == client_data.pid)
		drawPlayer(a.i,a.j,a.dir,AL,a.energy,1);
		else
				drawPlayer(a.i,a.j,a.dir,AL,a.energy,0);
	}
	for (int i=0;i<server_data.commando_count;i++)
     {   
		Commando c=server_data.commandos[i];
		if(c.pid == client_data.pid)
		drawPlayer(c.i,c.j,c.dir,COM,c.energy,1);
		else
				drawPlayer(c.i,c.j,c.dir,COM,c.energy,0);
	}
	if((server_data.commando_count==0)||(server_data.alien_count==0))
	{
		//GAME OVER
	}
}
//DRAWS ALL APLLES ON THE SCREEN
void displayApples()
{
	for (int i=0;i<server_data.apple_count;i++)
        {   
		Apple a=server_data.apples[i];
		drawApple(a.i,a.j);
	}
}

//GRAPHICS DISPLAY FUNCTION
void display()
{

	starting_j=0;

	/*int mypos;
	 if(getCommandoIndex(client_data.pid)!=-1)  
       	{mypos=getCommandoIndex(client_data.pid);
       	
    if(server_data.commandos[mypos].j> 6&& server_data.commandos[mypos].j<20)
    {
    		starting_j=server_data.commandos[mypos].j-6;
    }
    else if (server_data.commandos[mypos].j<6)
    {
    		starting_j=0;
    }
    else
    {
    		starting_j=13;
    }

       	}
       	
  else if(getAlienIndex(client_data.pid)!=-1)  
       	{mypos=getAlienIndex(client_data.pid);
    if(server_data.aliens[mypos].j> 6&& server_data.aliens[mypos].j<14)
    {
    		starting_j=server_data.aliens[mypos].j-6;
    }
    else if (server_data.aliens[mypos].j<6)
    {
    		starting_j=0;
    }
    else
    {
    		starting_j=7;
    }

  	
    }*/

    glClear(GL_COLOR_BUFFER_BIT);
   // glClearColor(0, 0, 0,0);
   
	// glColor3f(1, 1, 1);
	
	  glLineWidth(2);   
    drawLineLoopRectangle(45,925,955,15);//arena
    //drawLineLoopRectangle(25,985,975,935);
    drawLineLoopRectangle(1100,925,1450,15);//Scoreboard
   
     drawBackground();
    drawMapMatrix();
    displayAllBullets();
    displayPlayers();
    displayApples();
    
     drawPlayer(2,17,UP,pinfo.player_type,100,1);
    if(server_data.commando_count == 0 && server_data.alien_count !=0)
    	{
    	glColor3f( 1.0f, 1.0f, 1.0f );
		glRasterPos2f(170,960);
			if(pinfo.player_type == AL)
    			{
    			 			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) "Your Team Captured the Earth Congrates!! ");
    			}
    			else
    			{
    	
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) "You Could'nt Save Earth !!");
    			}
    			
    			 glutSwapBuffers();
    			
    			showAllData(-2);
    			terminateClient(-2);
    	}
    	
    	 if(server_data.alien_count == 0 && server_data.commando_count !=0)
    	{
    	
    	    	glColor3f( 1.0f, 1.0f, 1.0f );
		glRasterPos2f(170,960);
	 		if(pinfo.player_type == COM)
    			{
    			  glColor3f( 1.0f, 1.0f, 1.0f );

			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) "Your Team Saved the Earth Congrates!!");
			
			
    			}else
    			{
    			  glColor3f( 1.0f, 1.0f, 1.0f );
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) "You could'nt Captured the Earth!! ");
    			}

    			 glutSwapBuffers();
    			showAllData(-3);
    			terminateClient(-3);
    	}
    
    if(getCommandoIndex(client_data.pid)!=-1)  
       	{int  pos=getCommandoIndex(client_data.pid);
//       	printf("%s\n",server_data.commandos[pos].name);
       	displayScore(server_data.commandos[pos].name,server_data.commandos[pos].score,server_data.commandos[pos].energy);
       	}
       	
 if(getAlienIndex(client_data.pid)!=-1)  
       	{int  pos=getAlienIndex(client_data.pid);
  //     	printf("%s\n",server_data.aliens[pos].name);
       	displayScore(server_data.aliens[pos].name,server_data.aliens[pos].score,server_data.aliens[pos].energy);
       	}
    
    glutSwapBuffers();
   
}

//DRAW MAP ON THE SCREEN
void drawMapMatrix()
{
	int i,j;
	for(i=0;i<ROWS;i++)
	{	
		for(j=0;j<COLS;j++)
		{
			drawOnePosition(i,j,server_data.matrix1[i][j]);
		}
	}
}


//DRAW ONE BLOCK OF THE MATRIX
void drawOnePosition(int i,int j,PositionType t)
{
	int diffj;
	diffj=j-starting_j;
	if(diffj>0)
	{
		switch(t)
		{
			case NONE:  break;
			//case  TREE: glColor3f(1, 1, 0);drawTree(i,j);break;
			case  PTREE: glColor3f(1, 1, 0);drawPermanentTree(i,j);break;
			case  RIVER: glColor3f(1, 1, 0);drawRiver(i,j);break;
			case  MOUNTAIN: glColor3f(1, 1, 0);drawMountain(i,j);break;
			case  CIRCLE: glColor3f(1, 1, 0);drawCircleObstacle(i,j);break;
			case  BOX: glColor3f(1, 1, 0);drawBox(i,j);break;
		}
	}
}


float r1=0,g1=0,b1=1,r2=0,g2=0,b2=1,r3=0,g3=0,b3=1;



//STARTUP MENU
void disp(void){
    glBegin(GL_POLYGON);
  glColor3f(r3,g3,b3);
     glVertex2f(200,450);
     glVertex2f(450,450);
    glVertex2f(450,400);
    glVertex2f(200,400);
    glEnd();
		
	glColor3f( 1.0f, 1.0f, 1.0f );
	glRasterPos2f(300,435);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) "| P L A Y |");



	drawPlayer(1,7,LEFT,AL,100,1);
	drawPlayer(1,8,LEFT,AL,80,1);
	drawPlayer(3,7,LEFT,AL,60,0);

	drawPlayer(3,8,LEFT,AL,20,0);

	drawBullet(1,6);
	drawBullet(3,6);
	drawBullet(1,3);
	drawBullet(3,3);


	drawPlayer(1,1,RIGHT,COM,100,1);
	drawPlayer(1,2,RIGHT,COM,60,1);
	drawPlayer(3,1,RIGHT,COM,80,0);
	drawPlayer(3,2,RIGHT,COM,20,0);

	//glColor3f( 0.3f, 0.2f, 1.0f );
	//glRasterPos2f(300,50);
	//glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("CSP 701 ASSIGNMENT--4"));


	glColor3f( 1.0f, 0.0f, 0.0f );
	glRasterPos2f(320,170);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("ALIEN INVASION"));

	glColor3f( 0.0f, 1.0f, 0.0f );
	glRasterPos2f(280,220);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("COMMANDOS VS ALIENS"));


	glColor3f( 1.0f, 1.0f, 1.0f );
	glRasterPos2f(250,600);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("DEVELOPERS"));

	glRasterPos2f(180,630);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("ABHISHEK GUPTA (2012MCS2825)"));

	glRasterPos2f(180,660);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("SOURABH MANGAL (2012MCS2847)"));




	   glutSwapBuffers();
 }

//MOUSE DRAG HANDLER
void mousedrag(int x, int y)
{
   if((x>200 && x<450) && (y>200 && y<250))
		{
		   r1=0.48;g1=0;b1=0.11;	disp();
		}
	else if(((x>200 && x<450) && (y>300 && y<350)))
   		{ r2=0.48;g2=0;b2=0.11;	disp();}
	else if(((x>200 && x<450) && (y>400 && y<450)))
		{  r3=0.48;g3=0;b3=0.11;	disp();}
	else {r1=0;g1=0;b1=1;r2=0;g2=0;b2=1;r3=0;g3=0;b3=1;disp();}
}

void MouseButton(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
    {	//printf(" %d   %d  \n",x,y);
	if(state == GLUT_DOWN)
    {
       
		if(((x>200 && x<450) && (y>400 && y<450)))
		{
			  glColor3f( 1.0f, 1.0f, 1.0f );
				glRasterPos2f(200,100);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) "Please wait connecting to server ");
			glutPostRedisplay();
			glutSwapBuffers();
			sendRequest();
			
		start();
		
		glutHideWindow();//glutGetWindow());
		
		 glutCreateWindow("Alien Invasion -- Play Game ");
		glOrtho(0, 1500,0,1000,-10,10);
		glutFullScreen();
		glutMouseFunc(fire_mouse); 
		glutDisplayFunc(display);
		 glutSpecialFunc(keyEvent);

    glutKeyboardFunc(spaceEvent);
   glutSpecialFunc(keyEvent);
		}
    }
}
}

