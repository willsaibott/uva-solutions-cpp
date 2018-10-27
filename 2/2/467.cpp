/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 467 - Synching Signals
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
  int k = 0;
  string output = "";
  string line;
  string unable = "is unable to synch after one hour.\n";

  output.reserve(500000);

  while(getline(cin, line))
  {
    int time = 0, period, greatest = 0, least = 3600;
    bool keep = true;
    vector<int> periods;
    stringstream ss(line);
    output += "Set " + to_string(++k) + " ";

    // Read the input
    while (!ss.eof())
    {
      ss >> period;
      periods.push_back(period);
      greatest = max(greatest, period);
      least = min(least, period);
    }

    time = - 2 * greatest;
    while (keep && time <= 3600)
    {
      time += 2 * greatest;
      for (int ii = 0; ii < greatest - 5 && keep; ii++)
      {
        keep = (time + ii) < (least - 5);
        if (keep) continue;
        for (auto per = periods.begin();
                  per != periods.end();
                  per++)
        {
          keep = keep ||
                 ((time + ii) % (2 * (*per)) >= *per - 5);
        }

        if (!keep)
        {
          time += ii;
        }
      }
    }

    if (time > 3600)
    {
      output += unable;
    }
    else
    {
      int min = time / 60;
      int seconds = time % 60;
      output += "synchs again at " + to_string(min) +
                " minute(s) and " + to_string(seconds) +
                " second(s) after all turning green.\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}