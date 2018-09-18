#include <cstdio>
#include <iostream>
#ifdef system
#undef system
#endif // DEBUG
using namespace std;

int main(int argc,char** argv){
  string input, line;

  string query="curl -d '{ \"args\": \"test\"}' -H \"Content-Type: application/json\" -X POST http://ptsv2.com/t/gbordignon/post";
  system(query.c_str());

  cout << "OK";
  return 0;
}