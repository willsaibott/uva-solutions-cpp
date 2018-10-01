/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

typedef unsigned short ushort;

void updatePosition(int &byte, int bits);
int h2d(char c);

class Instruction
{
  string name;
  string params[3];
  int totalParams;

  public:

  Instruction(string instructionName, int params) :
                  name(instructionName),
                  totalParams(params) { }

  string * getParams() { return params; }

  int getNumberOfParams() { return totalParams; }

  static int readBytes(char* input, int &byte, int bytes)
  {
    int value = 0;

    for(int ii = 0; ii < bytes; ii++) {
      value = (value << 4) + h2d(input[byte++]);
    }

    value = value & 0x3FFF;
    return value;
  }

  string * setParams(char * input, int &byte)
  {
    for(int ii = 0; ii < totalParams; ii++) {
      stringstream ss;
      string param;
      int operand = (h2d(input[byte]) & (0xC)) >> 2;

      switch(operand)
      {
        case 0x00:
          ss << "R";
          break;
        case 0x01:
          ss << "$";
          break;
        case 0x02:
          ss << "PC+";
          break;
        case 0x03: break;
      }

      ss << readBytes(input, byte, 4);
      param = ss.str();
      this->params[ii] = param;
    }
    return params;
  }

  string to_string()
  {
    string str(name + " ");

    str += params[0];

    for(int ii = 1; ii < totalParams; ii++) {
        str += "," + params[ii];
    }
    return str + "\n";
  }
};

Instruction getInstruction(char* input, int &byte);

Instruction instructionMap[16] {
    Instruction("ADD",  2),
    Instruction("SUB",  2),
    Instruction("MUL",  2),
    Instruction("DIV",  2),
    Instruction("MOV",  2),
    Instruction("BREQ", 1),
    Instruction("BRLE", 1),
    Instruction("BRLS", 1),
    Instruction("BRGE", 1),
    Instruction("BRGR", 1),
    Instruction("BRNE", 1),
    Instruction("BR",   1),
    Instruction("AND",  3),
    Instruction("OR",   3),
    Instruction("XOR",  3),
    Instruction("NOT",  1)
  };

int main()
{
  string output = "";
  char buffer[500000], *p, *input;
  int pos = 0;

  p = input = buffer;
  scanf("%s", p);
  while (*(++p));

  while (*(input + pos))
  {
    Instruction instruction = getInstruction(input, pos);

    if (instruction.getNumberOfParams()*4 + 1 >= (p - input - pos))
    {
      scanf("%s", p);
      while (*(++p));
    }
    instruction.setParams(input, pos);

    output += instruction.to_string();
  }

  printf("%s", output.c_str());

  return(0);
}

int h2d(char hexchar)
{
  return (hexchar >= 'A') ? (hexchar - 'A' + 10) : (hexchar - '0');
}

Instruction getInstruction(char * input, int &byte)
{
  int opCode = h2d(input[byte++]);
  return instructionMap[opCode];
}