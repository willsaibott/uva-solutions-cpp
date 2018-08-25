/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

const char LIVING = 'O';
const char DEAD = ' ';
const int SIZE = 20;

void run(vector<string> &location)
{
  bool hasLivingBeing = false;
  int neighbors, imin, imax, jmin, jmax;
  vector<string> newLocation(SIZE, string(SIZE, DEAD));

  for(int ii = 0; ii < SIZE; ii++) {
    for(int jj = 0; jj < SIZE; jj++) {
      neighbors = (location[ii][jj] == LIVING ? -1 : 0);

      imin = max(ii - 1, 0);
      jmin = max(jj - 1, 0);
      imax = min(ii + 1, 19);
      jmax = min(jj + 1, 19);

      for(int iii = imin; iii <= imax; iii++) {
        for(int jjj = jmin; jjj <= jmax; jjj++) {
          if (location[iii][jjj] == LIVING)
          {
            neighbors++;
          }
        }
      }

      if (neighbors >= 4 || neighbors < 2)
      {
        newLocation[ii][jj] = DEAD;
      }
      else if (neighbors == 3)
      {
        newLocation[ii][jj] = LIVING;
      }
      else
      {
        newLocation[ii][jj] = location[ii][jj];
      }

      hasLivingBeing = hasLivingBeing ||
                       neighbors > 0 ||
                       newLocation[ii][jj] == LIVING;
    }
  }

  // for(int ii = 0; ii < SIZE; ii++) {
  //   for(int jj = 0; jj < SIZE; jj++) {
  //     location[ii][jj] = newLocation[ii][jj];
  //   }
  // }

  location = newLocation;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;

  // getline(cin, line); faster way
  // N = stoi(line);
  cin >> N;

  while(k++ < N)
  {
    int years, x, y;
    vector<string> location(SIZE, string(SIZE, DEAD));

    cin >> years;

    getline(cin, line); // skip empty line;

    if (!begin) output += "\n";
    else begin = false;

    output += "********************\n";

    while(getline(cin, line))
    {
      if (line.compare("") == 0) break;

      istringstream iss(line);
      iss >> x >> y;
      location[x - 1][y - 1] = LIVING;
    }

    int count = 0;
    do
    {
      for(int ii = 0; ii < SIZE; ii++) {
        output += location[ii] + "\n";
      }

      output += "********************\n";
      run(location);
    } while (++count < years);
  }

  // output += "\n";
  printf("%s", output.c_str());

  return(0);
}