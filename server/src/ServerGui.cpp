
//PRINTS ALL STATISTICS FOR GAME DEPENDING ON FLAG VALUE

void printStatistics(int flag)
{
	if(flag==-2)
	{
		clearScreen();
		printCenter("");
		printf("ALIEN TEAM DESTROYED THE EARTH\n");
		printCenter("ALIENS SURVIVED IN THE BATTLE\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     HEALTH\n");
		for(int i=0;i<server_data.alien_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.aliens[i].name,server_data.aliens[i].score,server_data.aliens[i].health);
		}
	}
	else if(flag==-3)
	{
		clearScreen();
		printCenter("");
		printf("COMMANDOS SAVED THE EARTH\n");
		printCenter("COMMANDOS SURVIVED IN THE BATTLE\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     HEALTH\n");
		for(int i=0;i<server_data.commando_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.commandos[i].name,server_data.commandos[i].score,server_data.commandos[i].health);
		}
	}
	else
	{
		clearScreen();
		printCenter("");
		printf("YOU LEFT THE GAME SUCCESSFULLY\n");
		printCenter("CURRENT STATUS OF THE GAME\n");
		printCenter("------------------------------\n");
		printCenter("TEAM ALIEN \n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     HEALTH\n");
		for(int i=0;i<server_data.alien_count;i++)
		{
			printCenter("");
			printf("%13ls %5ld %6ld\n",server_data.aliens[i].name,server_data.aliens[i].score,server_data.aliens[i].health);
		}
		printCenter("TEAM ALIEN\n");
		printCenter("------------------------------\n");
		printCenter("NAME          SCORE     HEALTH\n");
		for(int i=0;i<server_data.commando_count;i++)
		{
			printCenter("");
			printf("%13s %5d %6d\n",server_data.commandos[i].name,server_data.commandos[i].score,server_data.commandos[i].health);
		}
	}
	printCenter("");
	
}

