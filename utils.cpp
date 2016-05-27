#include "utils.h"

double Utils::get_distance(int x, int y, int x2, int y2){
  double dx = abs(x-x2);
  double dy = abs(y-y2);
  return sqrt(dx*dx + dy*dy);
}
