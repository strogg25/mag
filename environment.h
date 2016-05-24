#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <cstdio>
#include <cstdlib>
#include "phone.h"
#include "basestation.h"

#define MAX_STEP 100
#define NEW_PHONE_CHANCE 10   //Percentage
#define PHONE_DISCONNECT 8    //Percentage
#define MAX_PHONES 1000
#define MAX_BASESTATIONS 3

class Environment
{
private:
  int step_count;
  Phone* phone_list[MAX_PHONES];
  int phone_number;
  int phone_next_id;

  Basestation* basestation_list[MAX_BASESTATIONS];

public:
  void initialization();
  void step();
  void main_loop();
  vector<pair<int, int> > get_basestation_positions();
};

#endif
