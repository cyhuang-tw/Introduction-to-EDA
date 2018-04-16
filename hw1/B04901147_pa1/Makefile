rvi:main.o vMap.o
	g++ -o rvi -std=c++11 -O3 main.o vMap.o
	rm -f *.o
main.o:main.cpp vMap.o
	g++ -c -std=c++11 -O3 main.cpp
vMap.o:vMap.h vMap.cpp
	g++ -c -std=c++11 -O3 vMap.cpp

clean:
	rm -f *.o rvi