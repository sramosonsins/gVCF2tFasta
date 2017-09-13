#clean:
rm -rf build/Release/GNU-Linux/main.o

#compile:
make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
mkdir -p build/Release/GNU-Linux
rm -f "build/Release/GNU-Linux/main.o.d"
g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o main.cpp
/usr/bin/make -f Makefile CONF=Release

