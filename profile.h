#ifndef PROFILE_H_
#define PROFILE_H_

#include <cmath>

constexpr double kMaxVelocity = 1.0;
constexpr double kMaxAcceleration = 1.0;

class Profile {
public:
  struct ProfilePoint {
    double position;
    double velocity;
  };
  Profile(ProfilePoint current) { current_ = current; }
  void SetGoal(ProfilePoint goal) {
    double delta_v = goal.velocity - current_.velocity;
    double delta_s = goal.position - current_.position;
    double delta_t = std::abs(delta_v) / kMaxAcceleration;
    backwards_ = delta_t * (delta_v / 2 + current_.velocity) > delta_s;
    goal_ = backwards_ ? ProfilePoint({-goal.position, -goal.velocity}) : goal;
    current_ = backwards_
                   ? ProfilePoint({-current_.position, -current_.velocity})
                   : current_;
    CalculateTime();
  }
  const double GetTime() { return end_deccel_t_; }
  const ProfilePoint GetPoint(double t);

private:
  void CalculateTime();

  ProfilePoint current_;
  ProfilePoint goal_;

  double end_accel_t_;
  double end_const_t_;
  double end_deccel_t_;

  bool backwards_;
};

#endif // PROFILE_H_
