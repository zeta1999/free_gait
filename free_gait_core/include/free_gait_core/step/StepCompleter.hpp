/*
 * StepCompleter.hpp
 *
 *  Created on: Mar 7, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

// Free Gait
#include "free_gait_core/TypeDefs.hpp"
#include "free_gait_core/executor/State.hpp"
#include "free_gait_core/executor/AdapterBase.hpp"
#include "free_gait_core/step/Step.hpp"
#include "free_gait_core/base_motion/BaseAuto.hpp"
#include "free_gait_core/base_motion/BaseTrajectory.hpp"
#include "free_gait_core/leg_motion/EndEffectorMotionBase.hpp"
#include "free_gait_core/leg_motion/JointMotionBase.hpp"
#include "free_gait_core/leg_motion/Footstep.hpp"
#include "free_gait_core/leg_motion/LegMode.hpp"

namespace free_gait {

class StepCompleter
{
 public:
  StepCompleter(std::shared_ptr<free_gait::AdapterBase> adapter);
  virtual ~StepCompleter();
  bool complete(const State& state, const StepQueue& queue, Step& step) const;
  bool complete(const State& state, const Step& step, EndEffectorMotionBase& endEffectorMotion) const;
  bool complete(const State& state, const Step& step, JointMotionBase& jointMotion) const;
  bool complete(const State& state, const Step& step, const StepQueue& queue, BaseMotionBase& baseMotion) const;
  void setParameters(Footstep& footTarget) const;
  void setParameters(LegMode& legMode) const;
  void setParameters(BaseAuto& baseAuto) const;
  void setParameters(BaseTrajectory& baseTrajectory) const;

 protected:

  struct FootstepParameters
  {
    std::string profileType = "triangle";
    double profileHeight = 0.06;
    double averageVelocity = 0.07;
  } footTargetParameters_;

  struct LegModeParameters
  {
    double duration = 0.0025;
    std::string frameId = "base";
  } legModeParameters_;

  struct BaseAutoParameters
  {
    double averageLinearVelocity = 0.05;
    double averageAngularVelocity = 0.1;
    double supportMargin = 0.04;
    PlanarStance nominalPlanarStanceInBaseFrame;

    BaseAutoParameters()
    {
      Position2 position;
      position << 0.385, 0.25;
      nominalPlanarStanceInBaseFrame.emplace(LimbEnum::LF_LEG, position);
      nominalPlanarStanceInBaseFrame.emplace(LimbEnum::RF_LEG, Position2(Eigen::Vector2d(position(0), -position(1))));
      nominalPlanarStanceInBaseFrame.emplace(LimbEnum::LH_LEG, Position2(Eigen::Vector2d(-position(0), position(1))));
      nominalPlanarStanceInBaseFrame.emplace(LimbEnum::RH_LEG, Position2(Eigen::Vector2d(-position(0), -position(1))));
    }

  } baseAutoParameters_;

  struct BaseTrajectoryParameters
  {
    BaseTrajectoryParameters()
    {
    }

  } baseTrajectoryParameters_;

 private:
  std::shared_ptr<free_gait::AdapterBase> adapter_;
};

} /* namespace */