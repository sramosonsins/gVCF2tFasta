MyDir="build/Release/GNU-Linux"
#clean:
rm -r $MyDir
#compile:
make -f nbproject/Makefile-Release.mk $MyDir/main.o
mkdir $MyDir
#rm -f $MyDir+"/main.o.d"
g++ -std=c++0x -lz -c -O2 -MMD -MP -MF -o sources/*.cpp
mv *.o $MyDir
make -f Makefile CONF=Release
rm -- -o
