/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
 */

#include <iostream>
#include <algorithm>
#include <set>
#include <deque>
#include <stack>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;


bool push(deque<char> & st, string&temp, stack<char>& my_stack)
{
  if (temp.empty())
    return false;
  st.push_back('i');
  my_stack.push(temp.back());
  temp.pop_back();
  return true;
}

void rev_push(deque<char> & st, string&temp, stack<char>& my_stack)
{
  st.pop_back();
  temp.push_back(my_stack.top());
  my_stack.pop();
}

bool pop(deque<char> & st, stack<char>&my_stack, string& out, const string& target)
{
  size_t osize = out.size();
  if (my_stack.empty() || my_stack.top() != target[osize])
    return false;
  st.push_back('o');
  out.push_back(my_stack.top());
  my_stack.pop();
  return true;
}

void rev_pop(deque<char> & st, stack<char>&my_stack, string& out)
{
  st.pop_back();
  my_stack.push(out.back());
  out.pop_back();
}

void get_seq_rec(deque<char> & st,
                 string& temp,
                 stack<char>& my_stack,
                 string& out,
                 const string& target,
                 set<string>& res)
{
  if (out.size() == target.size())
  {
    string s;
    for (auto it = st.begin(); it != st.end(); it++)
    {
      s += *it; s += " ";
    }
    s.pop_back();
    res.insert(s);
    return;
  }

  if (push(st, temp, my_stack))
  {
    get_seq_rec(st, temp, my_stack, out, target, res);
    rev_push(st, temp, my_stack);
  }

  if (pop(st, my_stack, out, target))
  {
    get_seq_rec(st, temp, my_stack, out, target, res);
    rev_pop(st, my_stack, out);
  }
}

set<string> get_seqs(string& input, const string& target)
{
  set<string> seqs;
  string out;
  stack<char> my_stack;
  deque<char> st;
  out.reserve(target.size());
  std::reverse(input.begin(), input.end());
  get_seq_rec(st, input, my_stack, out, target, seqs);
  return std::move(seqs);
}

int main()
{
  string output = "";

  output.reserve(500000);

  while(!cin.eof())
  {
    string input, target;
    cin >> input >> target;
    cin.ignore();
    if (cin.fail()) break;

    output += "[\n";

    auto cinput  = input;
    auto ctarget = target;
    sort(cinput.begin(),  cinput.end());
    sort(ctarget.begin(), ctarget.end());

    if (input.size() && cinput == ctarget)
    {
      for (auto& seq: get_seqs(input, target))
      {
        output += seq;
        output.append("\n");
      }
    }

    output += "]\n";
  }

  printf("%s", output.c_str());

  return(0);
}