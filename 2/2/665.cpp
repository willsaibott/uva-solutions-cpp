/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 665 - False coin
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Measure
{
  int coinsToMeasure;
  vector<int> left, right;
  set<int> all;
  char veridict;

  public:

  Measure(int coinsToMeasure) : coinsToMeasure(coinsToMeasure)
  {
    left.reserve(10);
    right.reserve(10);
  }

  void addLeft(int l)
  {
    left.push_back(l);
    all.insert(l);
  }

  void addRight(int r)
  {
    right.push_back(r);
    all.insert(r);
  }

  void addVeridict(char v)
  {
    veridict = v;
  }

  vector<int> & getLeft() {return left;}
  vector<int> & getRight() {return right;}
  char getVeridict() {return veridict;}
  bool contain(int coin)
  {
    return all.count(coin);
  }
};

int removeFromSuspects(set<int> &suspects,
                       set<int> &lights,
                       set<int> &heavies,
                       set<int> &undefs,
                       set<int> &truthies,
                       int value)
{
  int removeds = 0;
  removeds += suspects.erase(value);
  removeds += lights.erase(value);
  removeds += heavies.erase(value);
  removeds += undefs.erase(value);
  removeds += (truthies.insert(value)).second;
  return removeds;
}

int determineFalsCoin(vector<Measure> &measures, int nCoins)
{
  set<int> lights, heavies, suspects, truthies, undefs;
  bool hasChanges = true;
  int falseCoin = 0;

  for (int ii = 1; ii <= nCoins; ii++)
  {
    undefs.insert(ii);
  }

  while (hasChanges && suspects.size() != 1)
  {
    hasChanges = false;

    for (auto measure = measures.begin();
              measure != measures.end();
              measure++)
    {
      char ver = measure->getVeridict();
      vector<int> left = measure->getLeft();
      vector<int> right = measure->getRight();
      int removeds = 0;

      if (ver == '=')
      {
        for (auto l = left.begin(), r = right.begin();
                  l != left.end(), r != right.end();
                  l++, r++)
        {
          removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        *l);
          removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        *r);
        }
      } else
      {

        if (ver == '<')
        {
          for (auto l = left.begin();
                    l != left.end();
                    l++)
          {
            if (suspects.count(*l))
            {
              if (heavies.count(*l))
              {
                removeds = removeFromSuspects(suspects,
                                              lights,
                                              heavies,
                                              undefs,
                                              truthies,
                                              *l);
              }
            } else if (!truthies.count(*l))
            {
              removeds += (lights.insert(*l)).second;
              removeds += (suspects.insert(*l)).second;
            }
          }

          for (auto r = right.begin();
                    r != right.end();
                    r++)
          {
            if (suspects.count(*r))
            {
              if (lights.count(*r))
              {
                removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        *r);
              }
            } else if (!truthies.count(*r))
            {
              removeds += (heavies.insert(*r)).second;
              removeds += (suspects.insert(*r)).second;
            }
          }
        } else if (ver == '>')
        {
          for (auto l = left.begin();
                    l != left.end();
                    l++)
          {
            if (suspects.count(*l))
            {
              if (lights.count(*l))
              {
                removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        *l);
              }
            } else if (!truthies.count(*l))
            {
              removeds += (heavies.insert(*l)).second;
              removeds += (suspects.insert(*l)).second;
            }
          }

          for (auto r = right.begin();
                    r != right.end();
                    r++)
          {
            if (suspects.count(*r))
            {
              if (heavies.count(*r))
              {
                removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        *r);
              }
            } else if (!truthies.count(*r))
            {
              removeds += (lights.insert(*r)).second;
              removeds += (suspects.insert(*r)).second;
            }
          }
        }

        for (auto undef = undefs.begin();
                  undef != undefs.end(); )
        {
          if (!measure->contain(*undef))
          {
            if (undef == undefs.begin())
            {
              removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        *undef);
              undef = undefs.begin();
            } else
            {
              int old = *undef;
              undef++;
              removeds = removeFromSuspects(suspects,
                                        lights,
                                        heavies,
                                        undefs,
                                        truthies,
                                        old);
            }
          } else
          {
            undef++;
          }
        }
      }

      hasChanges = hasChanges || removeds > 0;
    }
  }

  if (suspects.size() == 1)
  {
    falseCoin = *(suspects.begin());
  } else if (undefs.size() == 1)
  {
    falseCoin = *(undefs.begin());
  }

  return falseCoin;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    int nCoins, nWeights;
    cin >> nCoins >> nWeights;

    if (!begin || (begin = false)) output += "\n";

    vector<Measure> measures;
    int falseCoin = -1;

    for (int ii = 0; ii < nWeights; ii++)
    {
      int coinsToMeasure;
      cin>>coinsToMeasure;

      Measure m(coinsToMeasure);
      for (int jj = 0; jj < coinsToMeasure; jj++)
      {
        int c;
        cin >> c;
        m.addLeft(c);
      }

      for (int jj = 0; jj < coinsToMeasure; jj++)
      {
        int c;
        cin >> c;
        m.addRight(c);
      }

      char c;
      cin >> c;
      m.addVeridict(c);

      measures.push_back(m);
    }

    falseCoin = determineFalsCoin(measures, nCoins);

    output += to_string(falseCoin) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}
