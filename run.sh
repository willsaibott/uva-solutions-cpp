clear
export PS1='\u@\h: '
export CH='2/3/'
export UVA=$1
g++ -Wall -std=c++11 $CH$1.cpp -O2 -o build/$1
chmod +x build/*
./build/$1 < input/$CH$1 > output/$CH$1