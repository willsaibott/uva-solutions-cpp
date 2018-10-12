/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int gcd(int a, int b)
{
  return b == 0 ? a : gcd(b, (a % b));
}

string printFraction(int integer,
                     int rest,
                     int samples,
                     int module,
                     int total)
{
  string str;
  string mod;
  int numDigitsSamples, pad;
  char s[25];

  numDigitsSamples = ceil(log10(samples + 1));

  if (module)
  {
    mod = (integer >= 0 ?
           to_string(integer) :
           "- " + to_string(module));
    pad = mod.size();

    str += string(pad, ' ');
    sprintf(s, "%*d\n", numDigitsSamples, rest);
    str += s;
    str += mod + string(numDigitsSamples, '-') + "\n";
    str += string(pad, ' ');
    sprintf(s, "%*d\n", numDigitsSamples, samples);
    str += s;
  } else
  {
    pad = total >= 0 ? 0 : 2;

    if (pad) str += "  ";
    sprintf(s, "%*d\n", numDigitsSamples, rest);
    str += s;

    if (pad) str += "- ";
    str += string(numDigitsSamples, '-') + "\n";
    sprintf(s, "%*d\n", numDigitsSamples, samples);

    if (pad) str += "  ";
    str += s;
  }

  return str;
}

int main()
{
  int k = 0;
  string output = "";
  string line;
  int samples, input, total, integer,
      module, rest, gcdValue;

  output.reserve(500000);

  while(!cin.eof())
  {
    k++;
    total = module = rest = gcdValue = 0;
    cin >> samples;

    if (!samples) break;

    for (int ii = 0; ii < samples; ii++)
    {
      cin >> input;
      total += input;
    }

    integer = total / samples;
    module = abs(integer);
    rest = abs(total) % samples;
    gcdValue = gcd(rest, samples);
    rest = rest / gcdValue;
    samples = samples / gcdValue;

    output += "Case " + to_string(k) + ":\n";

    if (rest)
    {
      output += printFraction(integer,
                              rest,
                              samples,
                              module,
                              total);
    } else
    {
      output += (integer >= 0 ? to_string(integer) : "- " + to_string(module)) + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}