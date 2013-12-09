Shortestpaths.exe: main.o
	g++ -o Shortestpaths.exe main.o

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o *~ *.x *.exe a.out Shortestpaths
