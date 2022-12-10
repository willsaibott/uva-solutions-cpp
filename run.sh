clear
UVA=$1
CH='3/2/'
SOLUTION_VERSION=$2
g++ -Wall -std=c++11 $CH$UVA$SOLUTION_VERSION.cpp -O2 -o build/$UVA$SOLUTION_VERSION
chmod +x build/*
mkdir -p  output/$CH
time ./build/$UVA$SOLUTION_VERSION < input/$CH$UVA$SOLUTION_VERSION > output/$CH$UVA$SOLUTION_VERSION