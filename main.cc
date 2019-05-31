#include "profile.h"
#include <iostream>
#include <fstream>

int main() {
  Profile::ProfilePoint current;
  Profile::ProfilePoint goal;
  {
    goal.position = 1.0;
    goal.velocity = 0.0;
  }
  Profile profile(current);
  profile.SetGoal(goal);
  std::cout << profile.GetTime() << std::endl;
  std::ofstream csv("/tmp/output.csv");

  for (double t = 0; t < 2.0; t += 0.005) {
    csv << t << "," << profile.GetSetpoint(t) << "\n";
  }
}
