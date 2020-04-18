clear
export PS1='\u@\h: '
export CH='2/4/'
export UVA=$1
export SOLUTION_VERSION=$2
g++ -Wall -std=c++11 $CH$UVA$SOLUTION_VERSION.cpp -O2 -o build/$UVA$SOLUTION_VERSION
chmod +x build/*
time ./build/$UVA$SOLUTION_VERSION < input/$CH$UVA$SOLUTION_VERSION > output/$CH$UVA$SOLUTION_VERSION