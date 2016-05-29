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
  string chromosome;
public:
  Basestation(int x, int y, string chromosome);
  int assign_bandwith(int id);
  void remove_assigment(int id);
  int simple_algorithm(int id);
  int get_x();
  int get_y();
};

#endif
