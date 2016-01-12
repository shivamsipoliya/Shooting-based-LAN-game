server: ServerNetwork.o Objects.o Map.o ServerMain.o Alien.o Commando.o
	g++ -o server ServerNetwork.o Objects.o Map.o ServerMain.o Alien.o Commando.o -fpermissive -lpthread -lGLU -lGL -lglut -w
	rm *.o 
ServerNetwork.o: src/ServerNetwork.cpp
	g++ -c src/ServerNetwork.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
Objects.o : src/Objects.cpp
	g++ -c src/Objects.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
Map.o : src/Map.cpp
	g++ -c src/Map.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
ServerMain.o :src/ServerMain.cpp
	g++ -c   src/ServerMain.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
Alien.o :src/Alien.cpp
	g++ -c   src/Alien.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
Commando.o :src/Commando.cpp
	g++ -c   src/Commando.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
clean :
	rm server
run:
	./server 9216
	
	
	
	
