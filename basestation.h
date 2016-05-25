#ifndef BASESTATION_H
#define BASESTATION_H
#include <string>
using namespace std;

#define MAX_BANDWITH_SIZE 1000
class Basestation
{
private:
  int x, y;
  int bandwith_table[MAX_BANDWITH_SIZE];
  void* environment;
public:
  Basestation(int _x, int _y, void* _environment);
  int assign_bandwith(int id);
  void remove_assigment(int id);
  int get_x();
  int get_y();
};

#endif
