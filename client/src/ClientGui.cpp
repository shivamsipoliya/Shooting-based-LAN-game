int starting_j;
// DRAW A BULLET ON THE SCREEN
void drawBullet(int i,int j) 
{
	
	int x,y,diffj;
	diffj=j-starting_j;
	if(diffj>=0)
	{
		x=diffj*70+45+35;
		y=i*70+15+35;
		    glPointSize(6);
	    glColor3f(1, 0, 1);
	    glBegin(GL_POINTS);
	    glVertex2f(x, y);
	    glEnd();
    }
}

//DRAW A RECTANGLE ON THE SCREEN
void drawRectangle(int x1,int y1,int x2,int y2) 
{
 
    glBegin(GL_POLYGON);
     glVertex2f(x1, y2);
     glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glVertex2f(x1, y1);
    glEnd();
}

//DRAW A TRIANGULAR SHAPE ON THE SCREEN
void drawMountain(int x1,int y1 , int x2,int y2,int x3,int y3)
{ 
 glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x1,y1,0);    // V1

    glColor3f(0.0f, 1.0f, 0.0f);
       glVertex3f(x2,y2,0);   // V2

    glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x3,y3,0);    // V3

    glEnd();
}
//DRAW AN OBSTACLE
void drawcobstacle(int x1,int y1,int x2,int y2)
{
 
  drawMountain(x1,y1,x2,y1,x1+(x2-x1)/2,y2);
}

//DRAW PLAYER BOUNDRY
void drawplayerboundary(int x1,int y1,int x2,int y2)
{
	 glLineWidth(10);   
    glBegin(GL_LINE_LOOP);
   	 glColor3f(0.5f, 0.0f, 0.8f);
    glVertex2f(x1, y2);
     glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glVertex2f(x1, y1);
    glEnd();
 
}

//DRAW PLAYER ON THE SCREEN
void drawPlayer(int i,int j,Direction d, Ptype p ,int energy,int me)
{
	int x1,y1,x2,y2,x,y,diffj;
	diffj=j-starting_j;
	if(diffj<0)return;
	x1=diffj*70+45;
	y1=i*70+15;
	x2=(diffj+1)*70+45;
	y2=(i+1)*70+15;
	switch(d)
	{
		case LEFT: 
			 drawplayerboundary(x1+(x2-x1)/2 ,y1,x2,y2);	 

			if(p==COM)
			{
			glColor3f(0.5f, 0.35f, 0.05f);
			drawRectangle(x1,y1+2*(y2-y1)/5,x1+(x2-x1)/2,y1+3*(y2-y1)/5);		
			}
						
			else
			{  
			glColor3f(1.0f, 0.0f, 1.0f); //TOP GUN
			drawRectangle(x1+24,y1+2*(y2-y1)/5,x1+(x2-x1)/2,y1+3*(y2-y1)/5);		
			glColor3f(1.0f, 1.0f, 0.0f); //MIDDLE
			drawRectangle(x1+12,y1+2*(y2-y1)/5,x1+(x2-x1)/2-(35-24),y1+3*(y2-y1)/5);		
			glColor3f(0.5f, 0.35f, 0.05f); //TOP
			drawRectangle(x1,y1+2*(y2-y1)/5,x1+(x2-x1)/2-(35-12),y1+3*(y2-y1)/5);		
			}	
	
			if(p==COM)
		        glColor3f(0, 0, 1);
			else 
			 glColor3f(0, 1, 0);
	
			
			drawRectangle(x1+(x2-x1)/2 ,y1,x2-(35-(.35*energy)),y2);
			 glColor3f(1, 0, 0);			
			drawRectangle(x1+(x2-x1)/2 +(.35*energy),y1,x2,y2);


					 glColor3f(1, 1, 0);
			 if(me)
    			drawCircle(x2-17.5,y1+(y2-y1)/2,15);	//DRAW CIRCLE

			break;

		case RIGHT:

			 drawplayerboundary(x1,y1,x1+(x2-x1)/2,y2);	

			glColor3f(0.5f, 0.35f, 0.05f);
			drawRectangle(x1+(x2-x1)/2,y1+2*(y2-y1)/5,x2,y1+3*(y2-y1)/5);

			if(p==COM)
			{glColor3f(0.5f, 0.35f, 0.05f);
			drawRectangle(x1+(x2-x1)/2,y1+2*(y2-y1)/5,x2,y1+3*(y2-y1)/5);
			}			
			else
			{  glColor3f(1.0f, 0.0f, 1.0f); //gun bottom
			drawRectangle(x1+(x2-x1)/2,y1+2*(y2-y1)/5,x2-(35-12),y1+3*(y2-y1)/5);
			 glColor3f(1.0f, 1.0f, 0.0f); // gun middle
			drawRectangle(x1+(x2-x1)/2+12,y1+2*(y2-y1)/5,x2-(35-24),y1+3*(y2-y1)/5);
			 glColor3f(0.5f, 0.35f, 0.05f);  // gun top
			drawRectangle(x1+(x2-x1)/2+24,y1+2*(y2-y1)/5,x2,y1+3*(y2-y1)/5);
			}	


			if(p==COM)
		        glColor3f(0, 0, 1);
			else 
			 glColor3f(0, 1, 0);
			drawRectangle(x1+35-(.35*energy),y1,x1+(x2-x1)/2,y2);
			 glColor3f(1, 0, 0);
			drawRectangle(x1,y1,x1+(x2-x1)/2-.35*energy,y2);

					 glColor3f(1, 1, 0);
			 if(me)
    			drawCircle(x1+17.5,y1+(y2-y1)/2,15);	//circle
					 
			break;
		case UP:

		       drawplayerboundary(x1,y1,x2,y1+(y2-y1)/2);		
	
			if(p==COM)
			 glColor3f(0, 0, 1);
			else 
			 glColor3f(0, 1, 0);
			 drawRectangle(x1,y1+(35-.35*energy),x2,(y1+(y2-y1)/2));
			 glColor3f(1, 0, 0);
		    
			drawRectangle(x1,y1,x2,y1+35-(.35*energy));

						 glColor3f(1, 1, 0);
						 if(me)
  			drawCircle(x1+(x2-x1)/2,y1+(y2-y1)/4,15);	//circle			
			
			
			if(p==COM)
			{		 glColor3f(0.5f, 0.35f, 0.05f);
			drawRectangle(x1+2*(x2-x1)/5,y2,x1+3*(x2-x1)/5,y1+(y2-y1)/2);
			}			
			else
			{  glColor3f(1.0f, 0.0f, 1.0f); //gun bottom
			drawRectangle(x1+2*(x2-x1)/5,y2-(35-12),x1+3*(x2-x1)/5,y1+(y2-y1)/2);
			 glColor3f(1.0f, 1.0f, 0.0f);//gun middle
			drawRectangle(x1+2*(x2-x1)/5,y2-(35-24),x1+3*(x2-x1)/5,y1+(y2-y1)/2+12);
			 glColor3f(0.5f, 0.35f, 0.05f); //gun top
			drawRectangle(x1+2*(x2-x1)/5,y2,x1+3*(x2-x1)/5,y1+(y2-y1)/2+24);
			}	
			break;
		case DOWN:

			drawplayerboundary(x1,y1+(y2-y1)/2,x2,y2);		

			if(p==COM)
			{			 glColor3f(0.5f, 0.35f, 0.05f);
			drawRectangle(x1+2*(x2-x1)/5,y1,x1+3*(x2-x1)/5,y1+(y2-y1)/2);
			}			
			else
			{  glColor3f(1.0f, 0.0f, 1.0f); //gun bottom
			drawRectangle(x1+2*(x2-x1)/5,y1+24,x1+3*(x2-x1)/5,y1+(y2-y1)/2);
			 glColor3f(1.0f, 1.0f, 0.0f); //gun middle
			drawRectangle(x1+2*(x2-x1)/5,y1+12,x1+3*(x2-x1)/5,y1+(y2-y1)/2-(35-24));
			 glColor3f(0.5f, 0.35f, 0.05f); //gun top
			drawRectangle(x1+2*(x2-x1)/5,y1,x1+3*(x2-x1)/5,y1+(y2-y1)/2-(35-12));
			}	
			
			if(p==COM)
		         glColor3f(0, 0, 1);
			else 
			 glColor3f(0, 1, 0);
			drawRectangle(x1,y1+(y2-y1)/2,x2,y1+(y2-y1)/2+.35*energy);
			 glColor3f(1, 0, 0);
			drawRectangle(x1,y1+(y2-y1)/2+(.35*energy),x2,y2);


			 glColor3f(1, 1, 0);
			 if(me)
    			drawCircle(x1+(x2-x1)/2,y2-17.5,15);	//circle
			
		break;
	}
}
//DRAWS ALINE LOOP ON THE SCREEN
void drawLineLoopRectangle(float x1,float y1,float x2,float y2)
{
  glColor3f(0, 1, 0);
	 glBegin(GL_LINE_LOOP);
         glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
	
	
}
//DRAW A CIRCLE WITH A SPECIFIED RADIUS
void createcircle (int x, int y, int radius) {
 glColor3f(0, 1, 0);
  glBegin(GL_POLYGON);
  glVertex2f(x + radius, y);
  glVertex2f(x, y + radius);

  glVertex2f(x - radius, y);
  glVertex2f(x, y - radius);
  glEnd();

}

//DRAWS AN APPLE ON THE SCREEN
void drawApple(int i,int j)
{

   int r =70;
	int x1,y1,x2,y2,x,y,diffj;
	diffj=j-starting_j;
	if(diffj<0)return;
	x1=diffj*70+45;
	y1=i*70+15;
	x2=(diffj+1)*70+45;
	y2=(i+1)*70+15;                            
	glColor3f(1, 0, 0);
	drawRectangle(x1+r/4,y1+r/4,x2-r/4,y2-r/4);
	createcircle (x1+(x2-x1)/2,y1+(y2-y1)/2,r/4);
}


//DISPLAYS THE SCOREBOARD ON THE SCREEN
void displayScore(char name[], int score,int energy)
{
	
	glColor3f( 1.0f, 1.0f, 1.0f );
	glRasterPos2f(1200,825);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("YOUR SCORE "));

	glRasterPos2f(350,950);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("WELCOME TO ALIEN INVASION"));

	glRasterPos2f(1200,725);
	char scorea[20];
	sprintf(scorea,"   %d",score);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)scorea);

	glRasterPos2f(1200,625);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*) ("YOUR ENERGY"));
	glRasterPos2f(1200,525);
	char energya[20];
	sprintf(energya,"%d",energy);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)energya);

	glRasterPos2f(1200,325);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)name);

	int breakpoint;
	breakpoint=1200+energy*200/100;
	glColor3f( 0.0f, 1.0f, 0.0f );
	drawRectangle(1200,475,breakpoint,450);
	glColor3f( 1.0f, 0.0f, 0.0f );
	drawRectangle(breakpoint,475,1200+200,450);
	//draw energy line

}
//USED TO DRAW A CIRCLE
void drawCircle(float cx, float cy, float r )
{
int num_segments =30;
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = r;
	float y = 0;
	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
	 glFlush();

}

//DRAW A TREE ON THE SCREEN 
void drawTree(int i,int j)
{
	int x1,y1,x2,y2,x3,y3;
	x1=j*70+45;
	y1=i*70+15;
	x2=(j+1)*70+45;
	y2=(i+1)*70+15;
	 x3 = x1+(x2-x1)/2;
	y3 = y1+(y2-y1)/2;
	
 glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x1,y3,0);
    glVertex3f(x2,y3,0);  
    glVertex3f(x3,y2,0);   

    glEnd();
	glBegin(GL_LINES);
	glLineWidth(10);
	glColor3f(0.6f, 0.4f, 0.1f);
     glVertex3f(x3,y3,0);
	glVertex3f(x3,y1,0);
	glEnd();

}
//DRAWS AN OBSTACLE OF DIFFERENT KIND
void riverCall(int x1,int y1,int x2,int y2)
{
 
     glColor3f(0.0,0.5,1.0);
     glBegin(GL_POLYGON);
     glVertex2f(x1, y2);
     glVertex2f(x2, y2);
     glVertex2f(x2, y1);
     glVertex2f(x1, y1);
     glEnd();
     
     
      glColor3f(1.0,1.0,1.0);
     for(int i=1;i<6;i++){
     glLineWidth (1.0);
     glLineStipple (1, 0xAAAA);
     glBegin(GL_LINES); 
     glVertex2f (x1+4, y1+12*i);
     glVertex2f (x1+10, y1+12*i);
     
          glVertex2f (x1+24, y1+12*i);
     glVertex2f (x1+34, y1+12*i);
     
          glVertex2f (x1+44, y1+12*i);
     glVertex2f (x1+54, y1+12*i);
     
    
          glVertex2f (x1+60, y1+12*i);
     glVertex2f (x1+68, y1+12*i);
    
    

     glEnd();}
}

//DRAWS A MOUNTAIN ON THE SCREEN
void drawMountain(int i,int j)
{ 

int x1,y1,x2,y2,x3;
	x1=j*70+45;
	y1=i*70+15;
	x2=(j+1)*70+45;
	y2=(i+1)*70+15;
	 x3 = x1+(x2-x1)/2;
	

 glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x1,y1,0);    // A

    glColor3f(0.0f, 1.0f, 0.0f);
       glVertex3f(x2,y1,0);   // B

    glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x3,y2,0);    // C

    glEnd();
}

void drawCircleObstacle(float i, float j)
{

int x1,y1,x2,y2,r;
x1=j*70+45;
r=25;
	y1=i*70+15;
	x2=(j+1)*70+45;
	y2=(i+1)*70+15;
	
	float cx, cy;
	cx = x1+(x2-x1)/2;
	cy = y1+(y2-y1)/2;

int num_segments =30;
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;//we start at angle = 0
	float y = 0;
	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
	 glFlush();

}



//DRAW RIVER
void drawRiver(int i,int j)
{
     glColor3f(1.0,0.0,0.0);//red
	int x1,y1,x2,y2,x,y;
	x1=j*70+45;
	y1=i*70+15;
	x2=(j+1)*70+45;
	y2=(i+1)*70+15;
	 
	riverCall(x1,y1,x2,y2);
}


void drawBackground()
{
	/*int x1,y1,x2,y2,x,y;
	 for(int i=0;i<ROWS;i++)
    {
    		for(int j=0;j<COLS;j++)
    		{
    			
			x1=j*70+45;

			y1=i*70+15;
			x2=(j+1)*70+45;
			y2=(i+1)*70+15;
			x=x1;y=y1;
			glColor3f(0,1,0);
			for(x=x1;x<=x2;x=x+4)
			{
				for(y=y1;y<=y2;y=y+4)
				{
					glBegin(GL_POINTS);
					glVertex2f(x,y);
					glEnd();
				}
				
			}
	
    		}
    }*/
}


//DRAW A GOOD TRRE
void drawPermanentTree(float i,float j )
{


    float x1,y1,x2,y2,y3,r;
	x1=j*70+35;
	y1=i*70+15;
	x2=(j+1)*70+35;
	y2=(i+1)*70+15;
	y3 =y1;
	int r1; 
	r1 = 15;
	x1 = x1+(x2-x1)/2;
	y1 = y1+(y2-y1)/2;

	int num_segments =40;
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = r1;
	float y = 0;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x+x1+35, y+y2-17.5);
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x+x1+15, y+y2-17.5);
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	
	glEnd();
	glColor3f(0.6f, 0.4f, 0.1f);//brown
     glBegin(GL_POLYGON);
     glVertex2f(x1+32, y3);
     glVertex2f(x1+32+5, y3);
     glVertex2f(x1+32+5, y1);
     glVertex2f(x1+32, y1);
     glEnd();
     
}

//DRAWS A BOX KIND OF OBSTACLE
void drawBox(int i,int j)
{

	int x1, y1, x2, y2;
	
 x1=j*70+45;
	y1=i*70+15;
	x2=(j+1)*70+45;
	y2=(i+1)*70+15;
	
     glColor3f(0.0,1.0,0.0);//blue
     glBegin(GL_POLYGON);
     glVertex2f(x1, y2);
     glVertex2f(x2, y2);
     glVertex2f(x2, y1);
     glVertex2f(x1, y1);
     glEnd();
     
     
      glColor3f(0.0,0.0,0.0);//white
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
    
     glColor3f(0.0,0.0,1.0);//white
    glBegin(GL_LINES); 	              			
    glVertex2f(x1,y2);
    glVertex2f(x2,y1);
    glEnd();
    
    glColor3f(0.0,0.0,1.0);//white
    glBegin(GL_LINES); 	              			
    glVertex2f(x1+(x2-x1)/2,y2);
    glVertex2f(x1+(x2-x1)/2,y1);
    glEnd();
	
	glColor3f(0.0,0.0,1.0);//white
    glBegin(GL_LINES); 	              			
    glVertex2f(x1,y1+(y2-y1)/2);
    glVertex2f(x2,y1+(y2-y1)/2);
    glEnd();

}








