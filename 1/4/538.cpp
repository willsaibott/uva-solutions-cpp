/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

typedef long long ll;
using namespace std;
using Account = pair<string, ll>;

int main()
{
  int k = 0, persons, transactions;
  string output = "";
  string line, p1, p2;
  ll amount;
  bool begin = true, reverse;

  // output.reserve(1000000);

  while(!cin.eof())
  {
    cin >> persons >> transactions;
    cin.ignore();

    if (!begin || (begin = false)) cout << endl;//output += "\n";
    if (persons == 0)
      break;

    // output += "Case #" + to_string(++k) + "\n";
    cout << "Case #" + to_string(++k) + "\n";

    map<string, ll> accounts;
    for(int ii = 0; ii < persons; ii++) {
      getline(cin, line);
      accounts[line] = 0.0;
    }

    reverse = persons > transactions;

    for(int ii = 0; ii < transactions; ii++) {
      cin >> p1 >> p2 >> amount;
      cin.ignore();
      accounts[p2] = accounts[p2] + amount;
      accounts[p1] = accounts[p1] - amount;

      if (reverse)
      {
        // output += p2 + " " + p1 + " " + to_string(amount) + "\n";
        cout << p2 << " " << p1 << " " << amount << endl;
      }
    }

    if (!reverse)
    {
      // vector<Account> v(accounts.begin(), accounts.end());

      // sort(v.begin(), v.end(), [](const Account& a,
      //                             const Account& b) {
      //   ll diff = b.second - a.second;
      //   return (diff == 0 ?
      //           b.first.compare(a.first) < 0:
      //           diff < 0);
      // });

      // for ( auto it = v.begin(); it != v.end(); it++ )
      // {
      //   auto current (*it);

      //   output += "account[" + current.first + "] = " + to_string(current.second) + "\n";
      // }

      int count = 0;
      map<string, ll>::iterator last = accounts.begin();
      for ( auto it = accounts.begin(); it != accounts.end(); it++ ) {
        auto current = *(it);
        if (it == last) continue;

        amount = accounts[last->first];
        accounts[last->first]   -= amount;
        accounts[current.first] += amount;

        if (amount < 0)
        {
          // output += current.first + " " + last->first + " " +
          //           to_string(-amount) + "\n";
          cout << current.first << " " << last->first << " " <<
                    -amount <<  endl;
        }
        else if (amount > 0)
        {
          // output += last->first + " " + current.first + " " +
          //           to_string(amount) + "\n";
          cout << last->first << " " << current.first << " " <<
                    amount << endl;
        }
        last = (it);
        count++;
      }

      // if (count > persons - 1)
      // {
      //   output += "Failed/Error:";
      // }
      // output += "Count= " + to_string(count) + "\n";
      // output += "Persons= " + to_string(persons) + "\n";


      // for ( auto it = accounts.begin(); it != accounts.end(); it++ )
      // {
      //   auto current (*it);

      //   output += "account[" + current.first + "] = " + to_string(current.second) + "\n";
      // }
    }
  }

  // printf("%s", output.c_str());

  return(0);
}