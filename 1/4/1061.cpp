/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
// #include <sstream>
// #include <iterator>
// #include <string>

using namespace std;

typedef set<string> combination;

string all[] = {"O", "AB", "B", "A"};
string allRh[] = {"+-", "++", "--"};

void populateMap(map<string, combination> &m, map<string, vector<string>> &m2)
{
  set<string> s1;

  s1.insert("?O");
  s1.insert("OO");
  s1.insert("AO");
  s1.insert("BO");
  s1.insert("AA");
  s1.insert("BB");
  s1.insert("AB");
  m["O"] = s1;

  s1.clear();
  s1.insert("?B");
  s1.insert("AB");
  s1.insert("BO");
  s1.insert("BB");
  s1.insert("ABB");
  s1.insert("AAB");
  s1.insert("ABAB");
  s1.insert("ABO");
  m["B"] = s1;

  s1.clear();
  s1.insert("?A");
  s1.insert("AB");
  s1.insert("AO");
  s1.insert("AA");
  s1.insert("AAB");
  s1.insert("ABB");
  s1.insert("ABAB");
  s1.insert("ABO");
  m["A"] = s1;

  s1.clear();
  s1.insert("AB");
  s1.insert("AAB");
  s1.insert("ABB");
  s1.insert("ABAB");
  m["AB"] = s1;

  vector<string> v1;
  v1.push_back("O");
  v1.push_back("B");
  v1.push_back("A");
  m2["?AxO"] = v1;

  v1.clear();
  v1.push_back("O");
  v1.push_back("AB");
  v1.push_back("B");
  v1.push_back("A");
  m2["?AxA"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("B");
  m2["?AxB"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("B");
  m2["?AxAB"] = v1;

  v1.clear();
  v1.push_back("O");
  v1.push_back("B");
  v1.push_back("A");
  m2["?OxO"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("B");
  m2["?OxB"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("A");
  m2["?OxA"] = v1;

  v1.clear();
  m2["?OxAB"] = v1;

  v1.clear();
  v1.push_back("O");
  v1.push_back("B");
  v1.push_back("A");
  m2["?BxO"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("A");
  m2["?BxA"] = v1;

  v1.clear();
  v1.push_back("O");
  v1.push_back("AB");
  v1.push_back("B");
  v1.push_back("A");
  m2["?BxB"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("A");
  m2["?BxAB"] = v1;

  v1.clear();
  m2["?ABxO"] = v1;

  v1.clear();
  v1.push_back("O");
  v1.push_back("AB");
  v1.push_back("B");
  v1.push_back("A");
  m2["?ABxA"] = v1;

  v1.clear();
  v1.push_back("O");
  v1.push_back("AB");
  v1.push_back("B");
  v1.push_back("A");
  m2["?ABxB"] = v1;

  v1.clear();
  v1.push_back("AB");
  v1.push_back("B");
  v1.push_back("A");
  m2["?ABxAB"] = v1;
}

vector<string> run(string father,
                   string mother,
                   string child,
                   map<string, combination> &m,
                   map<string, vector<string>> &m2)
{
  char rh1, rh2;
  bool onlyNegative;
  vector<string> possibles;

  if (child == "?")
  {
    rh1 = father.back();
    rh2 = mother.back();
    father.pop_back();
    mother.pop_back();
    onlyNegative = rh1 == '-' && rh2 == '-';
    string both = (father > mother ?
                   mother + father:
                   father + mother);

    for(int ii = 0; ii < 4; ii++) {
      combination comb = m[all[ii]];

      if (comb.count(both))
      {
        possibles.push_back(all[ii] + "-");
        if (!onlyNegative)
        {
          possibles.push_back(all[ii] + "+");
        }
      }
    }
  }
  else
  {
    string both = (father == "?" ?
                   "?" + mother :
                   "?" + father);

    rh1 = both.back();
    rh2 = child.back();
    both.pop_back();
    child.pop_back();
    onlyNegative = !(rh1 == '-' && rh2 == '+');
    both += "x" + child;

    vector<string> s = m2[both];

    for ( auto it = s.begin(); it != s.end(); it++ ) {
      if (onlyNegative)
      {
        possibles.push_back(*it + "-");
      }
      possibles.push_back(*it + "+");
    }
  }

  return possibles;
}

int main()
{
  int k = 0;
  string output = "";
  string father, mother, child;
  map<string, combination> m;
  map<string, vector<string>> m2;
  // ostringstream oss;

  populateMap(m, m2);

  output.reserve(500000);

  while(true)
  {
    cin >> father >> mother >> child;
    cin.ignore();

    if (father == "E") break; // E N D

    output += "Case " + to_string(++k) + ": ";
    vector<string> possibles =
        run(father, mother, child, m, m2);

    string result;
    if (possibles.size())
    {
      string values;
      string lbracket = (possibles.size() == 1) ? "": "{";
      string rbracket = (possibles.size() == 1) ? "": "}";

      for ( auto it = possibles.begin(); it != possibles.end() -1; it++ ) {
        values += *it + ", ";
      }

      result = lbracket + values + possibles.back() +  rbracket;
    } else{
      result = "IMPOSSIBLE";
    }

    if (father == "?")
    {
      output +=  result +  " " +  mother + " " + child + "\n";
    } else if (mother == "?")
    {
      output += father + " " + result + " " + child + "\n";
    } else
    {
      output += father + " " + mother + " " + result + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}