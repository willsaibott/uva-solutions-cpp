/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

/**
 * B = Base address of the array
D = Number of dimensions in the array
Ld = Lower bound of dimension d
Ud = Upper bound of dimension d
CD = Array element size in bytes
Cd = Cd+1(Ud+1 − Ld+1 + 1) for 1 ≤ d < D
C0 = B − C1L1 − C2L2 − · · · − CDLD

A[i1, i2, . . . , iD] is calculated from the formula
C0+C1i1+C2i2 + · · · + CDiD,
 * */

typedef struct arr {
  string name;
  int base;
  int dimensions;
  int elemSize;
  vector<pair<int, int>> bounds;
  vector<int> Cs;
} Array;

int main()
{
  int k = 0;
  int N, R;
  string output = "";
  string line;
  map<string, Array> arrays;

  output.reserve(500000);
  cin >> N >> R;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    int lower, upper;
    Array array;
    cin >> array.name >> array.base
        >> array.elemSize >> array.dimensions;

    array.Cs = vector<int>(array.dimensions + 1);
    for (int ii = 0; ii < array.dimensions; ii++)
    {
      cin >> lower >> upper;
      array.bounds.push_back({ lower, upper });
    }

    array.Cs[array.dimensions] = array.elemSize;
    array.Cs[0] = array.base - array.Cs.back() * array.bounds[array.dimensions - 1].first;

    for (int ii = array.dimensions - 1; ii > 0; ii--)
    {
      array.Cs[ii] = array.Cs[ii + 1] *
          (array.bounds[ii].second - array.bounds[ii].first + 1);
      array.Cs[0] -= array.Cs[ii] * array.bounds[ii - 1].first;
    }
    arrays[array.name] = array;
  }

  k = 0;

  while(k++ < R && !cin.eof())
  {
    string name;
    int index, address;
    Array array;
    cin >> name;
    array = arrays[name];
    address = array.Cs[0];

    output += name + "[";
    for (int ii = 1; ii <= array.dimensions; ii++)
    {
      cin >> index;
      address += array.Cs[ii] * index;
      output += to_string(index) + ", ";
    }

    output.pop_back(); // ,
    output.pop_back(); // blank
    output += "] = " + to_string(address) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}