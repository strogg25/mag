#include "basestation.h"

Basestation::Basestation(int _x, int _y){
  x = _x;
  y = _y;
}

int Basestation::get_x(){
  return x;
}

int Basestation::get_y(){
  return y;
}
