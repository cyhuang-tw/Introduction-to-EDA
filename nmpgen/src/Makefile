nmpgen:main.o nmpMgr.o
	g++ -static -o nmpgen -std=c++98 -O3 main.o nmpMgr.o
main.o:main.cpp nmpMgr.o
	g++ -c -std=c++98 -O3 main.cpp
nmpMgr.o:nmpMgr.h nmpMgr.cpp
	g++ -c -std=c++98 -O3 nmpMgr.cpp

clean:
	rm -f main.o nmpMgr.o nmpgen


