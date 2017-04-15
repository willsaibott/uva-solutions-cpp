#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char *argv[])
{
  regex r(" [a - z]\\d{2} ");
  string replacement = " *** ";
  string str;
  while (getline(cin, str)) {
    cout << regex_replace(str, r, replacement) << endl;
  }


  return 0;
}
