#ifndef PHONE_H
#define PHONE_H

#include <utility>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

class Phone
{
private:
  int ID;
  int x;
  int y;
  int priority;
public:
  Phone(int _x, int _y, int _priority, int _ID, vector<pair<int, int> > basestations_positions);
  double get_distance(int x, int y, int x2, int y2);
  void select_station(vector<pair<int, int> > basestations_positions);
  int get_id();
};
#endif
