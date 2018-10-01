/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAX = 12 * 60;

int main()
{
  int k = 0, hour, minute, rest;
  int N;
  string output = "";
  string line;
  char s[10];

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    stringstream ss;
    getline(cin, line, ':');
    hour = stoi(line) % 12;
    getline(cin, line);
    minute = stoi(line);
    rest = MAX - (hour * 60 + minute);
    hour = (rest / 60 ? rest / 60 : 12);
    minute = rest % 60;

    sprintf(s, "%02d:%02d\n", hour, minute);
    output += s;
  }

  printf("%s", output.c_str());

  return(0);
}