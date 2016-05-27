#include "basestation.h"
#include "environment.h"

Basestation::Basestation(int _x, int _y, void* _environment){
  x = _x;
  y = _y;
  environment = _environment;
}

int Basestation::get_x(){
  return x;
}

int Basestation::get_y(){
  return y;
}

int Basestation::assign_bandwith(int id){
  string chromosome = "A";// ((Environment*)environment)->get_chromosome();

  //Simple algorithm
  if (chromosome == "A"){
    const int bandwith_simple = 100;
    for(int i = 0; i < MAX_BANDWITH_SIZE; i++){
      if (bandwith_table[i] == 0){
        for(int j = 0; j < bandwith_simple; j++)
          bandwith_table[i+j] = id;
        return bandwith_simple;
      }
    }
  return -1;
  }
  return -1;
}

void Basestation::remove_assigment(int id){
  for(int i = 0; i < MAX_BANDWITH_SIZE; i++){
    if (bandwith_table[i] == id)
      bandwith_table[i] = 0;
  }
}
