clear
export PS1='\u@\h: '
export CH='3/3/'
export UVA=$1
export SOLUTION_VERSION=$2
g++ -Wall -std=c++11 $CH$UVA$SOLUTION_VERSION.cpp -O2 -o build/$UVA$SOLUTION_VERSION
chmod +x build/*
mkdir -p  output/$CH
time ./build/$UVA$SOLUTION_VERSION < input/$CH$UVA$SOLUTION_VERSION > output/$CH$UVA$SOLUTION_VERSION