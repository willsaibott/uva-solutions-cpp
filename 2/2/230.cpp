/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <set>

using namespace std;

typedef struct Book {
  string title;
  string author;
} book;

struct Comparator
{
  inline bool operator() (const book &b1, const book &b2)
  {
    return (b1.author != b2.author ?
            b1.author < b2.author :
            b1.title < b2.title);
  }
};

int main()
{
  string output = "";
  string line;
  set<book, Comparator> lib;
  set<book, Comparator> borrowed;
  set<book, Comparator> returned;
  map<string, book> m;

  output.reserve(500000);

  while(true)
  {
    string title, author;
    int index;

    getline(cin, line);
    if ("END" == line) break;

    index = line.find(" by ");
    title = line.substr(0, index);
    author = line.substr(index + 4);

    book b = { title, author };
    lib.insert(b);
    m[title] = b;
  }

  while (true)
  {
    string title, command;
    int index = 7;

    getline(cin, line);

    if (line == "END") break;

    command = line.substr(0, index - 1);

    if (command == "SHELVE")
    {
      for (auto it = returned.begin();
                it != returned.end();
                it++)
      {
        pair<set<book, Comparator>::iterator, bool>
        p = lib.insert(*it);

        if (p.first != lib.begin())
        {
          auto last = prev(p.first);
          output += "Put " + p.first->title + " after " +
                    last->title + "\n";
        } else
        {
          output += "Put " + p.first->title + " first\n";
        }
      }
      output += "END\n";
      returned.clear();
    } else if (command == "RETURN")
    {
      title = line.substr(index);
      book b = m[title];
      returned.insert(b);
      borrowed.erase(b);
    } else
    {
      title = line.substr(index);
      book b = m[title];
      borrowed.insert(b);
      lib.erase(b);
      returned.erase(b);
    }
  }

  printf("%s", output.c_str());

  return(0);
}