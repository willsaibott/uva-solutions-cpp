/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void createMorseMap(map<string, char> &m);

int main()
{
  int k = 0;
  int N;
  bool begin = true;
  string output = "";
  string line, word;
  map<string, char> m;
  stringstream ss;


  output.reserve(500000);
  cin >> N;
  cin.ignore();

  createMorseMap(m);

  while(k++ < N)
  {
    getline(cin, line);
    ss = stringstream(line);

    if (!begin || (begin = false)) output += "\n";
    output += "Message #" + to_string(k) +  "\n";

    while (!ss.eof())
    {
      getline(ss, word, ' ');
      if (m[word] != ' ' ||
          (output.back() != ' ' && output.back() != '\n'))
        output += m[word];
    }

    while (output.back() == ' ') output.pop_back();
    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}

void createMorseMap(map<string, char> &m)
{
  m[".-"] = 'A';
  m[".---"] = 'J';
  m["..."] = 'S';
  m[".----"] = '1';
  m[".-.-.-"] = '.';
  m["---..."] = ':';
  m["-..."] = 'B';
  m["-.-"] = 'K';
  m["-"] = 'T';
  m["..---"] = '2';
  m["--..--"] = ',';
  m["-.-.-."] = ';';
  m["-.-."] = 'C';
  m[".-.."] = 'L';
  m["..-"] = 'U';
  m["...--"] = '3';
  m["..--.."] = '?';
  m["-...-"] = '=';
  m["-.."] = 'D';
  m["--"] = 'M';
  m["...-"] = 'V';
  m["....-"] = '4';
  m[".----."] = '\'';
  m[".-.-."] = '+';
  m["."] = 'E';
  m["-."] = 'N';
  m[".--"] = 'W';
  m["....."] = '5';
  m["-.-.--"] = '!';
  m["-....-"] = '-';
  m["..-."] = 'F';
  m["---"] = 'O';
  m["-..-"] = 'X';
  m["-...."] = '6';
  m["-..-."] = '/';
  m["..--.-"] = '_';
  m["--."] = 'G';
  m[".--."] = 'P';
  m["-.--"] = 'Y';
  m["--..."] = '7';
  m["-.--."] = '(';
  m[".-..-."] = '"';
  m["...."] = 'H';
  m["--.-"] = 'Q';
  m["--.."] = 'Z';
  m["---.."] = '8';
  m["-.--.-"] = ')';
  m[".--.-."] = '@';
  m[".."] = 'I';
  m[".-."] = 'R';
  m["-----"] = '0';
  m["----."] = '9';
  m[".-..."] = '&';
  m[""] = ' ';
}