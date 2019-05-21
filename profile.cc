#include "profile.h"
#include <cmath>
#include <iostream>

void Profile::CalculateTime() {
  // Let's assume the profile is truncated, so let's calculate the ends to make
  // it a full trapezoid. We can subtract these later

  double first_leg = current_.velocity / kMaxAcceleration;
  double first_leg_dist =
      0.5 * kMaxAcceleration * first_leg * first_leg; // 0.5at^2

  double last_leg = goal_.velocity / kMaxAcceleration;
  double last_leg_dist =
      0.5 * kMaxAcceleration * first_leg * first_leg; // 0.5at^2

  // Full trapezoid including the possible missing legs
  double full_dist =
      first_leg_dist + (goal_.position - current_.position) + last_leg_dist;
  double accel_t = kMaxVelocity / kMaxAcceleration;

  double const_dist = full_dist - (kMaxAcceleration * accel_t * accel_t);

  if (const_dist < 0) {
    // Accelerate for half the distance
    // 0.5 * full_dist = 0.5 at^2
    // full_dist = at^2
    // t = (full_dist / a)^(1/2)
    accel_t =
        std::sqrt(full_dist / kMaxAcceleration); // Accelerate half the distance
                                                 // each way, this is 0.5at^2
    const_dist = 0.0;
  }

  end_accel_t_ = accel_t - first_leg;
  end_const_t_ = end_accel_t_ + const_dist / kMaxVelocity;
  end_deccel_t_ = end_const_t_ + accel_t - last_leg;
}

const Profile::ProfilePoint Profile::GetPoint(double t) {
  ProfilePoint ret = current_;

  if (t < end_accel_t_) {
    ret.velocity += t * kMaxAcceleration;
    ret.position =
        current_.velocity * t + 0.5 * kMaxAcceleration * t * t; // vt + 0.5at^2
  } else if (t < end_const_t_) {
    ret.velocity = kMaxVelocity;
    ret.position += current_.velocity * end_accel_t_ +
                    0.5 * kMaxAcceleration * end_accel_t_ * end_accel_t_ +
                    kMaxVelocity * (t - end_accel_t_);
  } else if (t <= end_deccel_t_) {
    double time_left = end_deccel_t_ - t;
    ret.velocity =
        goal_.velocity +
        (time_left)*kMaxAcceleration; // Decceleration towards goal from
                                      // whatever peak was reached
    ret.position =
        goal_.position - (goal_.velocity * time_left +
                          0.5 * kMaxAcceleration * time_left * time_left);
  } else {
    return goal_;
  }
  return ret;
}
