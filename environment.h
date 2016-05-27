#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include "phone.h"
#include "basestation.h"

#define MAX_STEP 10000
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
  bool verbose;
  double data_sent;
  fstream output_file;
  Basestation* basestation_list[MAX_BASESTATIONS];

public:
  string chromosome;
  void initialization(string _chromosome, bool _verbose, int seed);
  void step();
  void main_loop();
  void info(string s);
  vector<pair<int, int> > get_basestation_positions();
  Basestation* get_basestation(int id);
  string get_chromosome();
  void send_data(int phone_x, int phone_y, int basestation_x, int basestation_y,
                 int bandwith);
};

#endif
