/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 855 - Lunch in Grid City
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  int avenues[50001];
  int streets[50001];

  while(k++ < N && !cin.eof())
  {
    int nAvenues, nStreets, nFriends;

    cin >> nAvenues >> nStreets >> nFriends;

    for (int ii = 0; ii < nFriends; ii++)
    {
      cin >> streets[ii] >> avenues[ii];
    }

    sort(streets, streets + nFriends);
    sort(avenues, avenues + nFriends);

    pair<int, int> meetingPoint;

    int median = (nFriends & 1) ? nFriends / 2 : (nFriends-1) / 2;
    meetingPoint.first  = streets[median];
    meetingPoint.second = avenues[median];

    output += "(Street: " + to_string(meetingPoint.first) +
              ", Avenue: " + to_string(meetingPoint.second) + ")\n";
  }

  printf("%s", output.c_str());

  return(0);
}