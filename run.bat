clear
set CH=2\2\
set UVA=%1
gcc -Wall -std=c++11 %CH%%1.cpp -O2 -lstdc++ -o build\%1.exe
.\build\%1.exe < input\%CH%%1 > output\%CH%%1