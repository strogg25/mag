#include "phone.h"
#include "basestation.h"
#include "environment.h"
#include "utils.h"

Phone::Phone(int _x, int _y, int _priority, int _ID, void* _environment){
  x = _x;
  y = _y;
  priority = _priority;
  ID = _ID;
  environment = _environment;
  select_station();
}

vector<pair<double, int> > Phone::create_distances_vector()
{
  vector<pair<int, int> > basestations_positions
                     = ((Environment*)environment)->get_basestation_positions();

  vector<pair<double, int> > distances;
  for(int i = 0; i < (int)basestations_positions.size(); i++){
    int x2 = basestations_positions[i].first;
    int y2 = basestations_positions[i].second;
    distances.push_back(make_pair(Utils::get_distance(x, y, x2, y2), i));
  }
  sort(distances.begin(), distances.end());
  return distances;
}

bool Phone::select_station(){
   vector<pair<double, int> > distances = create_distances_vector();
   assigned_basestation = -1;

   for(int i = 0; i < (int)distances.size(); i++){
      int id = distances[i].second;
      Basestation* basestation =
        ((Environment*)environment)->get_basestation(id);
      bandwith_assigned = basestation->assign_bandwith(get_id());

      //Successfull assignment
      if (bandwith_assigned != -1)
      {
        assigned_basestation = id;
        return true;
      }
   }
   return false;
}

double Phone::get_distance(int x, int y, int x2, int y2){
  double dx = abs(x-x2);
  double dy = abs(y-y2);
  return sqrt(dx*dx + dy*dy);
}

int Phone::get_id() {
  return ID;
}

int Phone::get_assigned_basestation()
{
  return assigned_basestation;
}

void Phone::send_data(){
  if (assigned_basestation == -1)
    return;
  Basestation* basestation =
    ((Environment*)environment)->get_basestation(assigned_basestation);
    ((Environment*)environment)->send_data(x, y,
      basestation->get_x(), basestation->get_y(), bandwith_assigned);
}

Phone::~Phone()
{
  Basestation* basestation =
    ((Environment*)environment)->get_basestation(assigned_basestation);
  basestation->remove_assigment(get_id());
}
