/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;

class Cargo
{
  int capacity;
  int used;
  int index;
  stack<int> packages;
  int static instances;

  public:

  Cargo(int capacity) : capacity(capacity)
  {
    index = ++instances;
    used = 0;
  };

  int getCapacity() const { return capacity; };

  int load(int l) {
    int loaded = 0;
    if (capacity - l >= 0)
    {
      packages.push(l);
      capacity -= l;
      loaded = (used += l);
    }

    return loaded;
  }

  bool operator() (const Cargo &c1, const Cargo &c2) const
  {
    return (c1.packages.size() != c2.packages.size() ?
            c1.packages.size() > c2.packages.size() :
            (c1.capacity != c2.capacity ?
             c1.capacity < c2.capacity :
             c1.index > c2.index));
  }

  bool operator< (const Cargo &c) const
  {
    return (packages.size() != c.packages.size() ?
            packages.size() > c.packages.size() :
            (capacity != c.capacity ?
             capacity < c.capacity :
             index > c.index));
  }

  int getIndex() const { return index; }

  stack<int> getStack() const { return packages; }

  bool pop() {

    if (packages.size())
    {
      packages.pop();
      return true;
    }
    return false;
  }

  int getLoaded() const { return used; }

  void static reset() { instances = 0; }
};

typedef priority_queue<Cargo, vector<Cargo>> Crc;

bool SortComparator(const Cargo & c1, const Cargo &c2)
{
  return c1.getIndex() < c2.getIndex();
}

int Cargo::instances = 0;

int main()
{
  string output = "";
  string line;
  bool begin = true;
  Crc crc;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n, capacity, pkg;
    size_t unloaded = 0;
    bool keep = true;
    cin >> n;

    Cargo::reset();

    for(int ii = 0; ii < n; ii++) {
      cin >> capacity;
      crc.push(Cargo(capacity));
    }

    if (!begin || (begin = false)) output += "\n";

    cin >> n;

    for(int ii = 0; ii < n; ii++) {
      cin >> pkg;
      Cargo c = crc.top();

      int loaded = c.load(pkg);
      keep = keep && loaded;
      if (!keep)
      {
        unloaded += pkg;
      } else
      {
        crc.pop();
        crc.push(c);
      }
    }

    cin.ignore();
    cin.ignore(); // blank line

    vector<Cargo> array;
    size_t maxSize = 0;
    size_t total = 0;
    size_t unused = 0;

    while (!crc.empty())
    {
      Cargo c = crc.top();
      maxSize = max(c.getStack().size(), maxSize);
      array.push_back(c);

      total += c.getLoaded();
      unused += c.getCapacity();
      crc.pop();
    }

    sort(array.begin(), array.end(), SortComparator);

    bool end = false;
    while (!end)
    {
      end = true;

      for ( auto it = array.begin(); it != array.end(); it++ ) {
        stack<int> loaded = it->getStack();

        if (loaded.size() < maxSize)
        {
          output += ": ";
        } else if (!maxSize && !loaded.size())
        {
          break;
        }
        else
        {
          output += to_string(loaded.top()) + " ";
          it->pop();
        }

        end = end && !loaded.size();
      }

      output.pop_back();
      output += "\n";
      maxSize = 0;
    }

    size_t nEquals = array.size() * 2 - 1;
    for(uint ii = 0; ii < nEquals; ii++) {
      output += "=";
    }

    output += "\n";

    for ( auto it = array.begin(); it != array.end(); it++ ) {
      output += to_string(it->getIndex()) + " ";
    }

    output.pop_back();
    output += "\n\ncargo weight: " + to_string(total) + "\n";
    output += "unused weight: " + to_string(unused) + "\n";
    output += "unloaded weight: " + to_string(unloaded) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}