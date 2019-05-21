#include "gtest/gtest.h"
#include "profile.h"
#include <fstream>

TEST(Profile, Test) {
  Profile profile({0., 0.});
  profile.SetGoal({1., 0.});
  double t = profile.GetTime();

  Profile::ProfilePoint prev_point;
  Profile::ProfilePoint point = profile.GetPoint(0.0);

  std::ofstream csv("/tmp/profile.csv");

  for (double i = 0; i < t; i += 0.005) {
    prev_point = point;
    point = profile.GetPoint(i);
    EXPECT_LE(point.velocity, kMaxVelocity);
    EXPECT_LE(point.velocity - prev_point.velocity, kMaxAcceleration * 0.005 + 1e-9);

    csv << i << "," << point.position << "," << point.velocity << "\n";
  }

  EXPECT_NEAR(profile.GetPoint(t).position, 1., 1e-9);
  EXPECT_NEAR(profile.GetPoint(t).velocity, 0., 1e-9);
}
