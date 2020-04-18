clear
export PS1='\u@\h: '
export DIR='input_generator'
g++ -Wall -std=c++11 $DIR/$1.cpp -O2 -o build/input_generator_$1
chmod +x build/input_generator_$1
./build/input_generator_$1 $2