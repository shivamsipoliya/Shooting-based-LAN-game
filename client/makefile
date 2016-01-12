Client: ClientMain.o
	g++ -o Client ClientMain.o -fpermissive -lpthread -lGLU -lGL -lglut -w
	rm *.o
ClientMain.o: src/ClientMain.cpp
	g++ -c  src/ClientMain.cpp -fpermissive -lpthread -lGLU -lGL -lglut -w
clean :
	rm Client
run:
	./Client localhost 9216
	

	
	
	
