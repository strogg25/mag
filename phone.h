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
  int x;
  int y;
  int priority;
  int ID;
  int bandwith_assigned;
  int assigned_basestation;
  void* environment;
public:
  Phone(int _x, int _y, int _priority, int _ID, void* environment);
  vector<pair<double, int> > create_distances_vector();
  bool select_station();
  int get_id();
  int get_assigned_basestation();
  void send_data();
  ~Phone();
};
#endif
