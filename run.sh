clear
export PS1='\u@\h: '
export CH='1/4/'
export UVA=$1
g++ -Wall -std=c++11 $CH$1.cpp -o build/$1
chmod +x build/*
./build/$1 < input/$1 > output/$1