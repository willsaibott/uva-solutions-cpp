#include <cstdio>
#include <iostream>

int main(){
std::string query1="cat code.cpp";
std::string query2="tac code.cpp | rev";
system(query1.c_str());
for(int ii = 0; ii < 1000000; ii++);
system("echo \"\"");
system(query2.c_str());
return 0;
}