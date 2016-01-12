
void initializeGame();
void drawmap_matrix();
void keyEvent(int key, int, int);
void spaceEvent(unsigned char key, int, int);
void timer(int);
void displayAllBullets();
int isObstacle(int i,int j);
int checkAppleCollide(int i,int j);
int checkBulletCollide(int i,int j);
int CheckPlayerCollide(int i,int j);
void destroyGenerateApple(int pos);
void moveAutoPlayers();
int checkCommandoCollide(int,int);
int getAlienIndex(int pid);
int getCommandoIndex(int pid);
void timer(int = 0);
void clrScreen();
void printCenter(char * p);


