#include "phone.h"

Phone::Phone(int _x, int _y, int _priority, int _ID, vector<pair<int, int> > basestations_positions){
  x = _x;
  y = _y;
  priority = _priority;
  ID = _ID;
  select_station(basestations_positions);
}

void Phone::select_station(vector<pair<int, int> > basestations_positions){
   vector<pair<double, int> > distances;
   for(int i = 0; i < basestations_positions.size(); i++){
     int x2 = basestations_positions[i].first;
     int y2 = basestations_positions[i].second;
     distances.push_back(make_pair(get_distance(x, y, x2, y2), i));
   }
   sort(distances.begin(), distances.end());
   for(int i = 0; i < distances.size(); i++){
      //wybierz stacje bazową
   }
}

double Phone::get_distance(int x, int y, int x2, int y2){
  double dx = abs(x-x2);
  double dy = abs(y-y2);
  return sqrt(dx*dx + dy*dy);
}

int Phone::get_id() {
  return ID;
}
