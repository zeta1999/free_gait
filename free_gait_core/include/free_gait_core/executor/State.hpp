/*
 * State.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include "free_gait_core/TypeDefs.hpp"
#include <quadruped_model/QuadrupedState.hpp>

// STD
#include <vector>

namespace free_gait {

class State : public quadruped_model::QuadrupedState
{
 public:
  State();
  virtual ~State();
  friend std::ostream& operator<<(std::ostream& out, const State& state);

  virtual void initialize(const std::vector<LimbEnum>& limbs, const std::vector<BranchEnum>& branches);

  bool getRobotExecutionStatus() const;
  void setRobotExecutionStatus(bool robotExecutionStatus);

  bool isSupportLeg(const LimbEnum& limb) const;
  void setSupportLeg(const LimbEnum& limb, bool isSupportLeg);
  unsigned int getNumberOfSupportLegs() const;

  bool isIgnoreContact(const LimbEnum& limb) const;
  void setIgnoreContact(const LimbEnum& limb, bool ignoreContact);

  bool hasSurfaceNormal(const LimbEnum& limb) const;
  const Vector& getSurfaceNormal(const LimbEnum& limb) const;
  void setSurfaceNormal(const LimbEnum& limb, const Vector& surfaceNormal);
  void removeSurfaceNormal(const LimbEnum& limb);

  bool isIgnoreForPoseAdaptation(const LimbEnum& limb) const;
  void setIgnoreForPoseAdaptation(const LimbEnum& limb, bool ignorePoseAdaptation);

  const JointPositions getJointPositions(const LimbEnum& limb) const;
  void setJointPositions(const LimbEnum& limb, const JointPositions& jointPositions);
  void setAllJointPositions(const JointPositions& jointPositions);
  void setAllJointVelocities(const JointVelocities& jointVelocities);

  const ControlSetup& getControlSetup(const BranchEnum& branch) const;
  const ControlSetup& getControlSetup(const LimbEnum& limb) const;
  void setControlSetup(const BranchEnum& branch, const ControlSetup& controlSetup);
  void setControlSetup(const LimbEnum& limb, const ControlSetup& controlSetup);
  void setEmptySetup(const BranchEnum& branch);
  void setEmptySetup(const LimbEnum& limb);

 private:
  // TODO Extend QuadrupedState class with:
  JointEfforts jointTorques_;
  LinearAcceleration linearAccelerationBaseInWorldFrame_;
  AngularAcceleration angularAccelerationBaseInBaseFrame_;

  // Free gait specific.
  std::unordered_map<BranchEnum, ControlSetup, EnumClassHash> controlSetups_;
  Force netForceOnBaseInBaseFrame_;
  Torque netTorqueOnBaseInBaseFrame_;
  std::unordered_map<LimbEnum, bool, EnumClassHash> isSupportLegs_;
  std::unordered_map<LimbEnum, bool, EnumClassHash> ignoreContact_;
  std::unordered_map<LimbEnum, bool, EnumClassHash> ignoreForPoseAdaptation_;
  std::unordered_map<LimbEnum, Vector, EnumClassHash> surfaceNormals_;
  bool robotExecutionStatus_;
};

} /* namespace */
