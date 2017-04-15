#include <iostream>
#include <ctime>
#include <cstring>
//#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
  char line[100];
  char weekDay[100];
  cin.getline(line, 100);
  while (strlen(line) > 1)
  {
    struct tm timeInfo;
    strptime(line, "%e %B %Y", &timeInfo);
    std::strftime(weekDay, 100, "%A", &timeInfo);
   printf("%s\n",  weekDay);
   cin.getline(line, 100);
  }
  return 0;
}
