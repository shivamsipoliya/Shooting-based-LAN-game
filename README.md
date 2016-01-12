# Shooting-based-LAN-game
************************************************ ALIEN INVASION GAME:MULTIPLAYER GAME *********************************************

******************************************* CREATED BY SHIVAM SIPOLIYA ******************************************

***************************************LINUX PLATFORM BASED USING OPENGL AND SOCKET PROGRAMMING *************************************  



**************PRE REQUISITES***********

1. g++ compiler with the opengl library.
2. Pthreads support in Linux.
3. A running LAN connection.


*************COMPILE AND RUN***********

SERVER SIDE:-
-------------

Connect to the internet.
The game requires a dedicated server. So first run the server in one terminal window using:
	#cd AlienInvasion
	#cd server 
	make run 
	
MENU:-

1. Enter the maximum number of player you want to support Eg:-1,2,3,4,5,.........
2. Enter the number of Automatic Commandoes.
3. Enter the number of Automatic Aliens.

Once the server is on, open a NEW terminal on same/different computer(Ensure that the host computer is connected to its clients through LAN for best results) and run the following commands after switching the new terminal:
	
CLIENT SIDE:-
------------

	#cd AlienInvasion 
	#cd client
        In client MakeFile enter the hostname or IP address of Machine on which server is started
        (Eg:- bismmad,deepak..(This are GCL mahine names!!!!)),or IP address(we can check IP by typing ifconfig on the terminal of server). 
	make run

MENU:-

1.Enter the playername.
2.Join in as Commando or Alien.

The game WILL NOT RUN until the required number of clients have connected to the network (through different terminals on same/different computers)

If server is not able to start because of busy port number change port number in Makefile of server as well as Makefile of client.

Note:-Port Number must be  same in server and all clients.


****************IN CASE OF TOO MANY SEGMENTATION FAULTS************** 


During the game you may notice that there are segmentation fault errors when you run the client. In that case re-run the server and then continue.
If it still persists then this is what you have to do,
	
	#cd AlienInvasion 
	#make clean 

This would remove all the executables. Now re-compile and run the game (from the beginning).



**********ON GAME******************

There is a battle going on between Aliens and Commandoes on earth,Alien wants to capture the planet earth and commandoes are here to save the earth.
Game will start when there is atleast one commandoes and one alien. 
Both aliens and commandoes has certain energy levels. Aliens  energy level decreases by running and by gun firing on them,and there is no means to increase the energy level of aliens;while commandoes energy can be increased by eating apples and decresead  by firing on them.Any player can join in at any time as a commandoe or as an alien on network.

*********SCORING CRITERIA**********

1.If Commandoes  kills Alien, Commandos score increases by 100 points.
2.Commandoes score increases  by 100 points,with each  apple eaten up by Commandos. 
3.If Commandoes destroys obstacles then he will gain 50 points.
4.If Alien  kills commandoes,alien score increases by 100 points.
5.If same team member kills each other i.e. alien kills alien and commandoes kill commandoes then player score decreases by 100.
6.Atlast whichever team wins alien/commandoes +1000 point is awarded to each team members present on the network. 
7.Finally,If all commandoes dies then alien wins and succeeded in taking over the earth and
  If all alien dies,commandoes wins and succeeded in protecting the earth.


***********FUNCTIONALITY*************

1.Upto 20 players can play simultaneously on network.
2.Any Player can leave or join at any time during the game.
3.When server shut downs all clients closes properly.
4.Player is not able to play until atleast one alien and one commando is present on the battle field(Quorum condition).
Eg:-Server Player added 3 commandos and now client player want to add as commando he will not be able to join the game until someone joined the game as alien.   
5.For each player its score is visible on its screen,with the energy levels.
6.When battle finishes score of each individual team member is displayed along with Team who wins the battle(Alien/Commandos).
7.With movement of Alien its energy level decreases.

(==========================================Enjoy the Game Cheers!!!!!!!!!!!!!!!!!!!!!!!!!!!!!============================================================)
