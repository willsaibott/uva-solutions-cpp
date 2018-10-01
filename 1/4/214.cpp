/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

string createStoreStatement(string instr, int operand)
{
  return instr + " $" + string(1, '0' + operand) + "\n";
}

string createStatement(string instr, char c)
{
  return instr + " " + string(1, c) + "\n";
}

string storeRegister(stack<char> &$operands, stack<char> &$reg)
{
  $operands.push($reg.top());
  $reg.pop();
  return createStoreStatement("ST", $operands.size() - 1);
}

string loadRegister(stack<char> & $operands,
                    stack<char> & $reg,
                    char operand = 0,
                    int offset = 0)
{
  if (operand)
  {
    $reg.push(operand);
    return createStatement("L", operand);
  } else
  {
    $reg.push($operands.top());
    $operands.pop();
    return createStoreStatement("L", $operands.size() + 1 + offset);
  }
}

string applyNegate(stack<char> &$operands, stack<char> &$reg)
{
  return "N\n";
}

string applyOperation(char op,
                      stack<char> &$operands,
                      stack<char> &$reg,
                      char next,
                      bool fromStorage)
{
  string output, instr;
  switch (op)
  {
    case '+':
      instr = "A";
      break;
    case '-':
      if (fromStorage)
      {
        output += applyNegate($operands, $reg);
        instr = "A";
      } else {
        instr = "S";
      }
      break;
    case '*':
      instr = "M";
      break;
    case '/':
      instr = "D";
      if (fromStorage)
      {
        output += storeRegister($operands, $reg);
        output += loadRegister($operands, $reg, 0, -2);
        output += createStoreStatement(instr, $operands.size());
        $operands.pop();
        return output;
      }
      break;
  }

  if (fromStorage)
  {
    $operands.pop();
    output += createStoreStatement(instr, $operands.size());
    if (next >= 'A')
      output += storeRegister($operands, $reg);
  } else
  {
    if (next)
      output += createStatement(instr, next);
    else
      output += createStatement(instr, $operands.size());
  }

  return output;
}

string run(string line)
{
  string output = "";
  stack<char> operands, reg, st;
  char c, next = 0, last = 0;
  uint index = 0;

  while (index < line.size())
  {
    c = line[index];
    next = (index < line.size() - 1 ? line[index + 1] : 0);

    if (st.size()) last = st.top();

    st.push(c);

    if (c >= 'A')
    {
      if (reg.size() && next && next >= '@')
      {
        output += storeRegister(operands, reg);
        output += loadRegister(operands, reg, c);
      } else if (!reg.size())
      {
        output += loadRegister(operands, reg, c);
      }
    }
    else if (c == '@')
    {
      output += applyNegate(operands, reg);
    } else {

      if (last < 'A')
      {
        output += applyOperation(c, operands, reg, last, true);
      } else
      {
        output += applyOperation(c, operands, reg, last, false);
      }
    }

    index++;
  }

  return output;
}

int main()
{
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);

  while(getline(cin, line))
  {
    if (!begin || (begin = false)) output += "\n";
    output += run(line);
  }

  printf("%s", output.c_str());

  return(0);
}