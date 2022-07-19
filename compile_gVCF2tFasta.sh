MyDir="build/Release/GNU-Linux"
#clean:
rm -r $MyDir
#compile:

#if [ "$(uname)" == "Darwin" ]; then
#    function _wget() { curl "${1}" -o $(basename "${1}") ; };
#    alias wget='_wget'
#fi

#zlib 1.2.11 installation (dependency)
#mkdir -p ./zlib
#wget http://zlib.net/zlib-1.2.11.tar.gz -P ./zlib
#tar -zxvf ./zlib/zlib-1.2.11.tar.gz -C ./zlib
#rm ./zlib/zlib-1.2.11.tar.gz
#cd ./zlib/zlib-1.2.11
#./configure
#make
#sudo make install

make -f nbproject/Makefile-Release.mk $MyDir/main.o
mkdir $MyDir
#rm -f $MyDir+"/main.o.d"
g++ -std=c++0x -c -O2 -MMD -MP -MF -o sources/*.cpp -lz
mv *.o $MyDir
make -f Makefile CONF=Release
rm -- -o

#if [ "$(grep -Ei 'debian|buntu|mint' /etc/*release)" ]; then
## do stuff
#fi
#if [ "$(grep -Ei 'fedora|redhat' /etc/*release)" ]; then
#...
