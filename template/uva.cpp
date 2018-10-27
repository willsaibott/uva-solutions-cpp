/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>


using namespace std;

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

  while(k++ < N && !cin.eof())
  {
    int n;
    cin >> n;

    if (!begin || (begin = false)) output += "\n";
    if (!n) break;

    output += line + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}