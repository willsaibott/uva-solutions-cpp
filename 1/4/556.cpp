/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int direction[][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

string run(vector<char> board[], int rows, int columns)
{
  int counter[rows][columns];
  int count[100] = {0};
  int *move = direction[0];
  pair<int, int> position, start = make_pair(rows - 1, 0), newPosition;
  bool out = false;
  int index = 0;
  char s[25];
  position = start;

  for(int ii = 0; ii < rows; ii++) {
    for(int jj = 0; jj < columns; jj++) {
      if (board[ii][jj] == '0')
        counter[ii][jj] = 0;
      else
        counter[ii][jj] = 5;
    }
  }

  while(!out || (position != start))
  {
    out = out || position != start;

    newPosition = make_pair(position.first + move[0],
                            position.second + move[1]);

    while (newPosition.first >= rows  ||
           newPosition.first < 0 ||
           newPosition.second >= columns ||
           newPosition.second < 0 ||
           (board[newPosition.first][newPosition.second] == '1'))
    {
      index = (index + 1) & 3;
      move = direction[index];
      newPosition = make_pair(position.first + move[0],
                              position.second + move[1]);
    }

    if (newPosition != position)
    {
      counter[position.first][position.second]++;
      position = newPosition;
    }

    index = (index + 3) & 3;
    move = direction[index];
  }
  // counter[position.first][position.second]++;

  for(int ii = 0; ii < rows; ii++) {
    for(int jj = 0; jj < columns; jj++) {
      count[counter[ii][jj]]++;
    }
  }

  sprintf(s, "%3d%3d%3d%3d%3d\n",
          count[0], count[1], count[2], count[3], count[4]);
  return string(s);
}

int main()
{
  uint rows, columns;
  string output = "";
  char input;

  output.reserve(500000);
  cin >> rows;
  cin >> columns;

  while(!cin.eof() &&  (rows  && columns))
  {
    vector<char> board[rows];

    for(uint ii = 0; ii < rows; ii++) {
      for(uint jj = 0; jj < columns; jj++) {
        cin >> input;
        board[ii].push_back(input);
      }
    }
    output += run(board, rows, columns);

    cin >> rows >> columns;
  }

  printf("%s", output.c_str());

  return(0);
}