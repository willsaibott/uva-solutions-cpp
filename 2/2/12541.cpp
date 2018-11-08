/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 12541 - Birthdates
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

class Person {
  string name;
  time_t time;

  public:
    Person() {}
    Person(string name, int day, int month, int year)
    : name(name) {
      tm t = { 0,0,0, day, month-1, year - 1900 };
      this->time = mktime(&t);
    }

    bool operator () (const Person &p) {
      return (this->time < p.time);
    }

    bool operator < (const Person &p) {
      return (this->time < p.time);
    }

    string getName() const {
      return name;
    }
};

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  vector<Person> persons;

  output.reserve(1000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    int day, month, year;
    string name;
    cin >> name >> day >> month >> year;
    persons.push_back(Person(name, day, month, year));
  }

  sort(persons.begin(), persons.end());

  output += persons.back().getName() + "\n" +
            persons.front().getName() + "\n";

  printf("%s", output.c_str());

  return(0);
}