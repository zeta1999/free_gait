/*
 * StepRosWrapper.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#include <free_gait_ros/BaseShiftDataRosWrapper.hpp>
#include <free_gait_ros/StepRosWrapper.hpp>
#include <free_gait_ros/SwingDataRosWrapper.hpp>
#include <ros/ros.h>
#include <string>


namespace free_gait {

StepRosWrapper::StepRosWrapper(std::shared_ptr<loco::LegGroup> legs,
                               std::shared_ptr<loco::TorsoBase> torso)
    : Step(legs, torso)
{

}

StepRosWrapper::~StepRosWrapper()
{

}

bool StepRosWrapper::fromMessage(const quadruped_msgs::Step& message)
{
  setStepNumber(message.step_number);

  const unsigned int nSwingLegs = message.swing_data.size();

  // Swing data.
  for (const auto& swingMessage : message.swing_data) {
    SwingDataRosWrapper swingData;
    if (!swingData.fromMessage(swingMessage)) return false;
    addSwingData(swingData.getName(), swingData);
  }

  // Base shift data.
  for (const auto& baseShiftMessage : message.base_shift_data) {
    BaseShiftDataRosWrapper baseShiftData;
    if (!baseShiftData.fromMessage(baseShiftMessage)) return false;

    // State type.
    Step::State state;

    if (baseShiftMessage.name == "pre_step")
      state = Step::State::PreStep;
    else if (baseShiftMessage.name == "at_step")
      state = Step::State::AtStep;
    else if (baseShiftMessage.name == "post_step")
      state = Step::State::PostStep;
    else {
      ROS_ERROR_STREAM("Invalid base shift state name: " << baseShiftMessage.name << ".");
      return false;
    }

    addBaseShiftData(state, baseShiftData);
  }

  return true;
}

} /* namespace */