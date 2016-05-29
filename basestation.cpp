#include "basestation.h"
#include "environment.h"

Basestation::Basestation(int x, int y, string chromosome)
:x(x), y(y), chromosome(chromosome) {}

int Basestation::get_x(){
  return x;
}

int Basestation::get_y(){
  return y;
}

int Basestation::simple_algorithm(int id){
  const int bandwith_simple = 100;
  for(int i = 0; i < MAX_BANDWITH_SIZE; i++){
    if (bandwith_table[i] == 0){
      for(int j = 0; j < bandwith_simple; j++)
        if (i+j < MAX_BANDWITH_SIZE)
          bandwith_table[i+j] = id;
      return bandwith_simple;
    }
  }
  return -1;
}

int Basestation::assign_bandwith(int id){
  if (chromosome == "A") return simple_algorithm(id);
  return -1;
}

void Basestation::remove_assigment(int id){
  for(int i = 0; i < MAX_BANDWITH_SIZE; i++){
    if (bandwith_table[i] == id)
      bandwith_table[i] = 0;
  }
}
