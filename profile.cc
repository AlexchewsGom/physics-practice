#include "profile.h"
#include <cmath>

const double Profile::GetTime(){
  double delta_x = (goal_.position - current_.position) / 2.0;

  double a = kMaxAcceleration;

  double t = std::sqrt((2 * delta_x) / (a));

  return t * 2.0;
}

const double Profile::GetSetpoint(double t) {
  double total_t = GetTime();

  bool accelerating = t < (total_t * pow(t,2))

  if (accelerating) {





}
