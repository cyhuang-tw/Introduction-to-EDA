ec:main.cpp cirMgr.o cirGate.o
	g++ -o ec -std=c++11 -g main.cpp cirMgr.o cirGate.o
cirMgr.o:cirMgr.h cirMgr.cpp cirGate.o
	g++ -c -std=c++11 -g cirMgr.cpp
cirGate.o:cirGate.h cirGate.cpp
	g++ -c -std=c++11 -g cirGate.cpp

clean:
	rm -f *.o ec



