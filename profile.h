#ifndef PROFILE_H_
#define PROFILE_H_

constexpr double kMaxVelocity = 1.0;
constexpr double kMaxAcceleration = 1.0;

class Profile {
public:
  struct ProfilePoint {
    double position;
    double velocity;
  };
  Profile(ProfilePoint current) {
    current_ = current;
  }
  void SetGoal(ProfilePoint goal) { 
    goal_ = goal; 
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
};

#endif // PROFILE_H_
