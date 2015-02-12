funix.out : directory.o funix.o main.o permissions.o Time.o  
	g++ -ansi -Wall -o funix.out directory.o funix.o main.o permissions.o Time.o  

directory.o : directory.cpp directory.h 
	g++ -ansi -Wall -c directory.cpp

funix.o : funix.cpp funix.h directory.h 
	g++ -ansi -Wall -c funix.cpp

main.o : main.cpp funix.h 
	g++ -ansi -Wall -c main.cpp

permissions.o : permissions.cpp permissions.h 
	g++ -ansi -Wall -c permissions.cpp

Time.o : Time.cpp Time.h 
	g++ -ansi -Wall -c Time.cpp

clean : 
	rm -f funix.out directory.o  funix.o  main.o  permissions.o  Time.o   
