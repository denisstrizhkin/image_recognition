CXX=g++ -std=c++11

EXEC_R=-o run
X_D=-o run_d

FLAGS_DEBUG=-g -O0
FLAGS_RELEASE=-O2

release: main_release.o
	$(CXX) $(FLAGS_RELEASE) main_release.o -o release

main_release.o: main.cpp
	$(CXX) $(FLAGS_RELEASE) -c main.cpp -o main_release.o

debug: main_debug.o
	$(CXX) $(FLAGS_DEBUG) main_debug.o -o debug

main_debug.o: main.cpp
	$(CXX) $(FLAGS_DEBUG) -c main.cpp -o main_debug.o

clean:
	rm -f *.o release debug
