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

int main()
{
  int k = 0;
  int N;
  string output = "";
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();
  cin.ignore(); // blank line;

  while(k++ < N)
  {
    bool halted = false;
    uint reg[10] = { 0 };
    uint instr, op1, op2;
    uint counter = 0, total = 0;
    vector<int> ram(1000, 0);
    string memory = "start";

    while (!cin.eof())
    {
      getline(cin, memory);
      if (memory == "") break;
      ram[total] = stoi(memory);
      total++;
    }

    if (!begin || (begin = false)) output += "\n";

    for ( auto mem = ram.begin();
          mem != ram.end() && !halted && (mem - ram.begin() <= total);
          mem++ )
    {
      instr = (*mem) / 100;
      op1 = ((*mem) / 10 ) % 10;
      op2 = (*mem) % 10;
      counter++;

      switch (instr)
      {
        case 1: halted = true; break;
        case 2:
          reg[op1] = op2;
          break;
        case 3:
          reg[op1] = (reg[op1] + op2) % 1000;
          break;
        case 4:
          reg[op1] = (reg[op1] * op2) % 1000;
          break;
        case 5:
          reg[op1] = reg[op2];
          break;
        case 6:
          reg[op1] = (reg[op1] + reg[op2]) % 1000;
          break;
        case 7:
          reg[op1] = (reg[op1] * reg[op2]) % 1000;
          break;
        case 8:
          reg[op1] = ram[reg[op2]];
          break;
        case 9:
          ram[reg[op2]] = reg[op1];
          total = max(reg[op2], total);
          break;
        case 0:
          if (reg[op2])
          {
            mem = ram.begin() + reg[op1] - 1;
            total = max(uint(mem - ram.begin()), total);
          }
          break;
      }
    }

    output += to_string(counter) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}