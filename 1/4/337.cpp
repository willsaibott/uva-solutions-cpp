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

void move(int &row, int &col, int roffset = 0, int coffset = 0)
{
  row = max(min(9, row + roffset), 0);
  col = max(min(9, col + coffset), 0);
}

void erase(int row, int col, vector<string> &terminal)
{
  for(int ii = col; ii < 10; ii++) {
    terminal[row][ii] = ' ';
  }
}

void print(vector<string> &terminal,
           int &row,
           int &col,
           char c,
           bool isInsertMode = false)
{
  if (isInsertMode)
  {
    terminal[row] = terminal[row].substr(0, col) +
                    string(1, c) +
                    terminal[row].substr(col);
  } else
  {
    terminal[row][col] = c;
  }
  move(row, col, 0, 1);
}

string formatTerminal(vector<string> terminal)
{
  string output;
  output.reserve(200);

  for(int ii = 0; ii < 10; ii++) {
    output += "|" + terminal[ii].substr(0, 10) + "|\n";
  }

  output += "+----------+\n";

  return output;
}

int main()
{
  int k = 0;
  int N, row, col;
  string output = "";
  string line;
  char command, c;
  bool insertMode;
  vector<string> empty = {
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
  };

  output.reserve(500000);

  while(!cin.eof())
  {
    cin >> N;
    cin.ignore();
    if (!N) break;
    insertMode = false;
    row = col = 0;
    output += "Case " + to_string(++k) + "\n+----------+\n";
    vector<string> terminal = empty;

    for(int ii = 0; ii < N; ii++) {
      getline(cin, line);
      // line.push_back("\n");
      for(uint jj = 0; jj < line.size(); jj++) {
        c = line[jj];
        if (c == '\n') break;
        if (c == '^')
        {
          command = line[++jj];
          switch(command)
          {
            case 'b': move(row, col, 0, -col); break;
            case 'c': terminal = empty; break;
            case 'd': move(row, col, 1); break;
            case 'e': erase(row, col, terminal); break;
            case 'h': move(row, col, -row, -col); break;
            case 'i': insertMode = true; break;
            case 'o': insertMode = false; break;
            case 'r': move(row, col, 0, 1); break;
            case 'l': move(row, col, 0, -1); break;
            case 'u': move(row, col, -1); break;
            case '^':
              print(terminal, row, col, command, insertMode);
              break;
            default:
              c = line[++jj];
              if (isdigit(c) && isdigit(command))
              {
                move(row, col,
                     (command - '0') - row, (c - '0') - col);
              }
          }
        } else
        {
          print(terminal, row, col, c, insertMode);
        }
      }
    }

    output += formatTerminal(terminal);
  }

  printf("%s", output.c_str());

  return(0);
}