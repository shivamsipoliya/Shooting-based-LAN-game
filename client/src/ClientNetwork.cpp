pthread_t thread;
pthread_t print_thread;//THREAD FOR PRINTING
int sockfd, portno, n;//SERVER SOCKET AND PORT NUMBER
struct sockaddr_in serv_addr;//IP OF SERVER
struct hostent *server;
Playerinfo pinfo;
Recv_client_struct client_data;
Server_struct server_data, new_server_data;
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
//CLEARS THE SCREEN
void clrScreen()
{
	system("clear");
	printf("\n\n\n\n\n\n");
	
}
//MOVE CURSOR TO THE CENTER
void printCenter(char * p)
{
	for(int i=0;i<20;i++)printf(" ");
	printf("%s",p);
}

//INITIALIZE CLIENT
int clientInit(int portno, char host[25])
{
		system("setterm -term linux -back green -fore white -bold on -clear");	
	
	//printf("Prot no is %d , host is %s", portno,host);
	int n;
	int choice;
	clrScreen();
	printCenter("PLAYER NAME : ");
	gets(pinfo.name);
	clrScreen();
	printCenter(" 1 FOR ALIEN OR 2 FOR COMMANDO : ");
	scanf("%d",&choice);
	if(choice==1)
	{
		pinfo.player_type=AL;
		client_data.player_type=AL;
	}
	else if (choice==2)
	{
		pinfo.player_type=COM;
		client_data.player_type=COM;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
       error("ERROR CONNECTING SERVER !!\n");
       close(sockfd);
       return -1;
    }
     printCenter("WELCOME TO ALIEN INVASION \n");
    printCenter("");
    //printf("YOUR PLAYER ID IS %d \n",client_data.pid);
    printCenter("ENJOY THE GAME !!\n"); 
    printCenter("PLEASE WAIT GAME IS STARTING\n");
    //n = recv(sockfd,&new_server_data,sizeof(server_data),0);
   
    return 0;

}
//SEND REQUEST TO THE SERVER
int sendRequest()
{
	n = send(sockfd,&pinfo,sizeof(Playerinfo),0);
    if(n<0)
    {
    		close(sockfd);
    		return -1;
    }
    n = recv(sockfd,&client_data.pid,sizeof(client_data.pid),0);
    if(client_data.pid==0)
    {
    		printf("PLAYERS LIMIT EXCEEDED\n");
    		close(sockfd);
    		return -1;
    }
     printCenter("WELCOME TO ALIEN INVASION \n");
    printCenter("");
    printf("YOUR PLAYER ID IS %d \n",client_data.pid);
    printCenter("ENJOY THE GAME !!\n"); 
    printCenter("PLEASE WAIT GAME IS STARTING\n");
    n = recv(sockfd,&new_server_data,sizeof(server_data),0);
   
    return 0;
}

//STARTS CLIENT THREAD TO RECEIVE DATA FROM SERVER AND DISPLAY
void start()
{
	pthread_create(&thread,NULL,keepReceivingData,NULL);

	if(pthread_create(&print_thread,NULL,keepRePainting,NULL))
			printf("starting print thread\n");	
}

//KEEP IN LOOP TO RECEIVE DATA
void keepReceivingData()
{
	int n;
	while(1)
	{
 		n = recv(sockfd,&new_server_data,sizeof(server_data),0);
    		if (n < 0) 
   	      {
   	      	
   	      	error("ERROR keepReceivingData from socket");
   	      }
   	      else
   	      {
   	      	server_data=new_server_data;
			//printf("DATA RECEIVED\n");
   	      }
	}
}


//UPDATE SCREEN
void keepRePainting()
{
while(1)
{
//printf("keepRePainting\n");
glutPostRedisplay();

}
}

//SEND KEY PRESSED TO THE SERVER
void sendKeyToServer(char key)
{
	client_data.key=key;
	send(sockfd,&client_data,sizeof(client_data),0);
}

//PRINT ALL DATA OF THE SERVER
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
		printCenter("NAME          SCORE     energy\n");
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
		printf("YOU LEFT THE GAME SUCCESSFULLY\n");
		printCenter("CURRENT STATUS OF THE GAME\n");
		printCenter("------------------------------\n");
		printCenter("TEAM COMMANDO \n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     energy\n");
		for(int i=0;i<server_data.alien_count;i++)
		{
			printCenter("");
			printf("%13ls %5ld %6ld\n",server_data.aliens[i].name,server_data.aliens[i].score,server_data.aliens[i].energy);
		}
		printCenter("TEAM ALIEN\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     energy\n");
		for(int i=0;i<server_data.commando_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.commandos[i].name,server_data.commandos[i].score,server_data.commandos[i].energy);
		}
	}
	
}
//CLOSE CLIENT
void terminateClient(int retkey)
{
	
	sendKeyToServer(retkey);
	if(retkey!=-5)
	{
		usleep(5000000);
		sendKeyToServer(-1);
	}
	else
		sendKeyToServer(-1);
	close(sockfd);
	exit(0);
}



