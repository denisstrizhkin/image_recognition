CXX=g++ -std=c++11

EXEC_R=-o run
X_D=-o run_d

FLAGS_DEBUG=-g -O0
FLAGS_RELEASE=-O2

# DEBUG
debug: main_debug.o neuralNet_debug.o
	$(CXX) $(FLAGS_DEBUG) main_debug.o neuralNet_debug.o -o debug

neuralNet_debug.o: neuralNet.cpp
	$(CXX) $(FLAGS_DEBUG) -c neuralNet.cpp -o neuralNet_debug.o

main_debug.o: main.cpp
	$(CXX) $(FLAGS_DEBUG) -c main.cpp -o main_debug.o

# RELEASE
release: main_release.o neuralNet_release.o
	$(CXX) $(FLAGS_RELEASE) main_release.o neuralNet_release.o -o release

neuralNet_release.o: neuralNet.cpp
	$(CXX) $(FLAGS_RELEASE) -c neuralNet.cpp -o neuralNet_release.o

main_release.o: main.cpp
	$(CXX) $(FLAGS_RELEASE) -c main.cpp -o main_release.o

clean:
	rm -f *.o release debug
