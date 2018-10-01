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
#include <set>

using namespace std;

class MTA;

class MTAEntry
{
  string name;
  string parentName;

public:
  const string admd, country, prmd, on;

  MTAEntry(string parentName,
           string name,
           string country,
           string admd,
           string prmd,
           string on)
    : parentName(parentName), name(name), country(country),
      admd(admd), prmd(prmd), on(on)
  { };

  MTAEntry(string name,
           string country,
           string admd,
           string prmd,
           string on)
    : parentName(""), name(name), country(country),
      admd(admd), prmd(prmd), on(on)
  { };

  MTAEntry(MTAEntry &&entry)
  : parentName(entry.parentName), name(entry.name), country(entry.country),
    admd(entry.admd), prmd(entry.prmd), on(entry.on)
  { }

  MTAEntry(const MTAEntry &entry)
  : parentName(entry.parentName), name(entry.name), country(entry.country),
    admd(entry.admd), prmd(entry.prmd), on(entry.on)
  { }

  const string &getName() const { return name; };
  const string to_string() const
  {
    return parentName + "-" + name + " " + country + " " +
           admd + " " +  prmd + " " + on;
  }

  MTAEntry* setParent(string str)
  {
    parentName = str;
    return this;
  }

  MTAEntry* setName(string str)
  {
    name = str;
    return this;
  }

  MTAEntry operator = (const MTAEntry &entry)
  {
    return entry;
  }
};

bool MTAEntryComparator (const MTAEntry &entry1, const MTAEntry &entry2)
{
  if (entry1.country != entry2.country)
  {
    return entry1.country < entry2.country;
  } else if (entry1.admd != entry2.admd)
  {
    return entry1.admd < entry2.admd;
  } else if (entry1.prmd != entry2.prmd)
  {
    return entry1.prmd < entry2.prmd;
  } else if (entry1.on != entry2.on)
  {
    return entry1.on < entry2.on;
  }
  return false;
}

class MTA
{
  string name = "";
  public:
    MTA() = default;
    MTA(MTA && mta) : name(mta.getName()), entries(mta.entries) { };
    MTA(string name) : name(name) {};
    MTA(const MTA &mta) {
      this->name = mta.name;
      this->entries = mta.entries;
    };

    vector<MTAEntry> entries;
    string getName() {return name; };

    static bool matches(const string &str1, const string str2) {
      return str1 == "*" || str1 == str2;
    }

    vector<MTAEntry>::iterator
    find(const MTAEntry &entry2)
    {
      return find_if(entries.begin(),
                     entries.end(),
                     [entry2](const MTAEntry& entry1)
      {
        return matches(entry1.country, entry2.country) &&
               matches(entry1.admd, entry2.admd) &&
               matches(entry1.prmd, entry2.prmd) &&
               matches(entry1.on, entry2.on);
      });
    }

    int bitmap = 0;
};

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;
  int entriesCount;
  string name, entryName, country, admd, prmd, on;
  string UNABLE_TO_ROUTE = " unable to route at ";
  string CIRCULAR_ROUTING = " circular routing detected by ";

  output.reserve(500000);
  cin >> N;
  while(!cin.eof())
  {
    map<string, MTA> mtas;

    for(int ii = 0; ii < N; ii++) {
      cin >> name >> entriesCount;
      MTA mta(name);

      for(int jj = 0; jj < entriesCount; jj++) {
        cin >> entryName >> country >> admd >> prmd >> on;
        MTAEntry entry(name, entryName, country, admd, prmd, on);

        mta.entries.push_back(entry);
      }

      mtas.insert(make_pair(name, mta));
    }

    int messages = 0;
    cin >> messages;

    if (!begin || (begin = false)) output += "\n";
    output += "Scenario # " + to_string(++k) + "\n";

    for(int ii = 0; ii < messages; ii++) {
      cin >> name >> country >> admd >> prmd >> on;
      MTAEntry entry(name, country, admd, prmd, on);
      bool isUnknown = true;
      bool isCircular = false, stop = false;
      set<string> sent;

      output += to_string(ii + 1) + " -- ";

      while(!stop)
      {
        auto it = mtas[name].find(entry);
        isUnknown = it == mtas[name].entries.end();
        stop = isUnknown || name == it->getName();

        if (!isUnknown && !stop)
        {
          if (!sent.insert(name).second)
          {
            stop = isCircular = true;
          } else
          {
            entry.setName(it->getName())->setParent(name);
            name = it->getName();
          }
        }
      }

      if (isUnknown)
      {
        output += "unable to route at " + name + "\n";
      } else if (isCircular)
      {
        output += "circular routing detected by " + name + "\n";
      } else {
        output += "delivered to " + name + "\n";
      }
    }

    cin >> N;
  }

  output += "\n";
  printf("%s", output.c_str());

  return(0);
}