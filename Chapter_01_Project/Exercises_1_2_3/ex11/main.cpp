#include <iostream>

using namespace std;

class Grammar
{
  static string line;
  static int pos;

public:
  static double eval(string str)
  {
    line = str;
    double x = 0;
    pos = - 1;
    nextChar();
    return x = parseExpression();
  }

  static void nextChar()
  {
    while (line[++pos] == ' ' && pos < (int)line.size());
  }

  static bool eat(char target)
  {
    while (line[pos] == ' ') pos++;
    if (line[pos] == target)
    {
      nextChar();
      return true;
    }
    return false;
  }

  static double parseExpression()
  {
    double x = parseTerm();
    for (;;)
    {
      if (eat('+'))
        x += parseTerm();
      else if (eat('-'))
        x -= parseTerm();
      else
        return x;
    }
  }

  static double parseTerm()
  {
    double x = parseFactor();
    for (;;)
    {
      if (eat('*'))
        x *= parseFactor();
      else if (eat('/'))
        x /= parseFactor();
      else
        return x;
    }
  }

  static double parseFactor()
  {
    if (eat('+')) return parseFactor();
    if (eat('-')) return -parseFactor();

    double x;
    int startPos = pos;
    if (eat('('))
    {
      x = parseExpression();
      eat(')');
    } else if ((line[pos] >= '0' && line[pos] <= '9') || line[pos] == '.')
    {
      std::size_t size = 0;
      while ((line[pos] >= '0' && line[pos] <= '9') || line[pos] == '.')
        nextChar();
      x = std::stod(&line[startPos], &size);
    } else {
      throw new exception;
    }
    return x;
  }
};

string Grammar::line = "";
int Grammar::pos = - 1;

int main(int argc, char *argv[])
{
  string line;
  while (std::getline(cin, line))
  {
    try {
    cout << "Input: " << line << endl <<
            "output: " << Grammar::eval(line) << endl;
    } catch (exception e)
    {
      printf("%s", e.what());
    }
  }
  return 0;
}
