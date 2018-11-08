/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 450 - Little Black Book
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>


using namespace std;

class Person
{
  string title;
  string firstName;
  string familyName;
  string address;
  string homePhone;
  string workPhone;
  string campusBox;
  string department;

  public:
    Person(string title, string firstName, string familyName,
           string address, string homePhone, string workPhone,
           string campusBox, string department)
           : title(title), firstName(firstName), familyName(familyName),
             address(address), homePhone(homePhone), workPhone(workPhone),
             campusBox(campusBox), department(department)
          { }

   string to_string() const
   {
     string str = "----------------------------------------\n";

     str += title + " " + firstName + " " + familyName + "\n";
     str += address + "\n";
     str += "Department: " + department + "\n";
     str += "Home Phone: " + homePhone + "\n";
     str += "Work Phone: " + workPhone + "\n";
     str += "Campus Box: " + campusBox + "\n";
     return str;
   }

   bool operator() (const Person &p2) const
   {
     return p2.familyName != familyName ?
           familyName < p2.familyName :
           firstName < p2.firstName;
   }

   bool operator<  (const Person &p2) const
   {
     return p2.familyName != familyName ?
           familyName < p2.familyName :
           firstName < p2.firstName;
   }
};

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  string department;
  set<Person> people;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    string title, firstName, familyName, address, home, work, campus;
    getline(cin, department);

    while (true)
    {
      getline(cin, line);
      if (line == "") break;

      stringstream ss(line);

      getline(ss, title,',');
      getline(ss, firstName,',');
      getline(ss, familyName,',');
      getline(ss, address,',');
      getline(ss, home,',');
      getline(ss, work,',');
      getline(ss, campus);

      people.insert(
        Person(title, firstName, familyName, address,
               home, work, campus, department));
    }
  }

  for (auto person = people.begin();
        person != people.end();
        person++)
  {
    output += person->to_string();
  }

  printf("%s", output.c_str());

  return(0);
}