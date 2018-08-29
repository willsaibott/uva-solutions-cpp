/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

string majorScales[][7] =
  { {"A", "B", "C#", "D", "E", "F#", "G#"},
    {"Bb", "C", "D", "Eb", "F", "G", "A"},
    {"B", "C#", "D#", "E", "F#", "G#", "A#"},
    {"C", "D", "E", "F", "G", "A", "B"},
    {"Db", "Eb", "F", "Gb", "Ab", "Bb", "C"},
    {"D", "E", "F#", "G", "A", "B", "C#"},
    {"Eb", "F", "G", "Ab", "Bb", "C", "D"},
    {"E", "F#", "G#", "A", "B", "C#", "D#"},
    {"F", "G", "A", "Bb", "C", "D", "E"},
    {"Gb", "Ab", "Bb", "Cb", "Db", "Eb", "F"},
    {"G", "A", "B", "C", "D", "E", "F#"},
    {"Ab", "Bb", "C", "Db", "Eb", "F", "G"},};

void populateMap(map<string, int> &m)
{
  m["A"]  = 0;
  m["A#"] = m["Bb"] = 1;
  m["B"]  = m["Cb"] = 2;
  m["C"]  = m["B#"] = 3;
  m["C#"] = m["Db"] = 4;
  m["D"]  = 5;
  m["D#"] = m["Eb"] = 6;
  m["E"]  = m["Fb"] = 7;
  m["E#"] = m["F"] = 8;
  m["F#"] = m["Gb"] = 9;
  m["G"]  = 10;
  m["G#"] = m["Ab"] = 11;
}

void populateIntervalMap(map<string, int> &m)
{
  m["SECOND"] = 1,
  m["THIRD"] = 2,
  m["FOURTH"] = 3,
  m["FIFTH"] = 4,
  m["SIXTH"] = 5,
  m["SEVENTH"] = 6,
  m["OCTAVE"] = 0;
}

// pair<string*, map<string, int>> &
//   getScale(string note, map<string, int> m)
// {
//   static map<string, pair<string*, map<string, int>>>
//       scales;

//   if (!scales.count(note))
//   {
//     string * scale = majorScales[m[note]];
//     map<string, int> indexes;

//     for(int ii = 0; ii < 7; ii++) {
//       indexes[scale[ii]] = ii;
//     }

//     scales[note] = make_pair(scale, indexes);
//   }

//   return scales[note];
// }

string* getScale(string note, map<string, int> &m)
{
  static map<string, string*> scales;

  if (!scales.count(note))
  {
    string * scale = majorScales[m[note]];
    scales[note] = scale;
  }

  return scales[note];
}

string getInterval(string line,
                   string* scale,
                   map<string, int> &intervalMap)
{
  string output = "invalid note for this key";
  string direction, interval, base;
  stringstream ss = stringstream(line);
  int indexBase = 0, pos, offset;
  bool forward;
  if (ss.eof()) return "";

  ss >> base;
  ss >> direction;
  ss >> interval;

  while (indexBase < 7 && scale[indexBase] != base)
    indexBase++;

  if (indexBase < 7)
  {
    forward = (direction == "UP");
    offset = intervalMap[interval];
    pos = forward?
          (indexBase + offset) % 7:
          (indexBase - offset + 7) % 7;

    output = direction + " " + interval + " > " + scale[pos];
  }

  return (base + ": " + output + "\n");
}

int main()
{
  string output;
  string note, line, interval;
  bool begin = true;
  map<string, int> m, intervals;
  stringstream ss;

  populateMap(m);
  populateIntervalMap(intervals);

  output.reserve(500000);
  output = "";

  while(!cin.eof())
  {
    getline(cin, note);

    if (!begin) output += "\n";
    begin = false;

    if (note.empty()) break;

    output += "Key of " + note + "\n";

    getline(cin, line);
    ss = stringstream(line);

    while(!ss.eof())
    {
      getline(ss, interval, ';');
      output += getInterval(interval,
                            getScale(note, m),
                            intervals);
    }
  }

  printf("%s", output.c_str());

  return(0);
}