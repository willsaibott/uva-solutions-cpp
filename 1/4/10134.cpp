/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define FISH 0
#define BAIT 1
#define LUNCH 2

size_t simulate(vector<int> &input)
{
  size_t counter = 0;
  uint last = 0;
  uint bait = 0;
  uint fishing = 0;

  for ( auto it = input.begin(); it != input.end(); it++ ) {
    switch(*it)
    {
      case FISH:
        if ((bait / 2)  &&
            ((last >= 6 && fishing >= 2) || !counter))
        {
          counter++;
          last = 0;
          fishing = 0;
          bait-=2;
        } else
        {
          if (bait / 2) fishing++;
          last++;
        }
        break;
      case BAIT:
        bait = min(bait + 1, uint(6));
      case LUNCH:
        last++;
        break;
    }
  }

  return counter;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();
  cin.ignore(); // blank line

  while(k++ < N)
  {
    vector<int> input;
    while (!cin.eof())
    {
      getline(cin, line);
      if (line == "") break;
      switch(line[0])
      {
        case 'l':
          input.push_back(LUNCH);
          break;
        case 'b':
          input.push_back(BAIT);
          break;
        case 'f':
          input.push_back(FISH);
          break;
      }
    }

    if (!begin || (begin = false)) output += "\n";
    output += to_string(simulate(input)) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}