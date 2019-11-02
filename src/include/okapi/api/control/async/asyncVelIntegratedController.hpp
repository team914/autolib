/*
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/control/async/asyncVelocityController.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/api/util/timeUtil.hpp"
#include <memory>

namespace okapi {
/**
 * Closed-loop controller that uses the V5 motor's onboard control to move. Input units are whatever
 * units the motor is in.
 */
class AsyncVelIntegratedController : public AsyncVelocityController<double, double> {
  public:
  /**
   * Closed-loop controller that uses the V5 motor's onboard control to move. Input units are
   * whatever units the motor is in. Throws a std::invalid_argument exception if the gear ratio is
   * zero.
   *
   * @param imotor The motor to control.
   * @param ipair The gearset.
   * @param imaxVelocity The maximum velocity after gearing.
   * @param itimeUtil The TimeUtil.
   * @param ilogger The logger this instance will log to.
   */
  AsyncVelIntegratedController(const std::shared_ptr<AbstractMotor> &imotor,
                               const AbstractMotor::GearsetRatioPair &ipair,
                               std::int32_t imaxVelocity,
                               const TimeUtil &itimeUtil,
                               const std::shared_ptr<Logger> &ilogger = Logger::getDefaultLogger());

  /**
   * Sets the target for the controller.
   */
  void setTarget(double itarget) override;

  /**
   * Gets the last set target, or the default target if none was set.
   *
   * @return the last target
   */
  double getTarget() override;

  /**
   * Returns the last error of the controller. Does not update when disabled.
   */
  double getError() const override;

  /**
   * Returns whether the controller has settled at the target. Determining what settling means is
   * implementation-dependent.
   *
   * If the controller is disabled, this method must return true.
   *
   * @return whether the controller is settled
   */
  bool isSettled() override;

  /**
   * Resets the controller's internal state so it is similar to when it was first initialized, while
   * keeping any user-configured information.
   */
  void reset() override;

  /**
   * Changes whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   */
  void flipDisable() override;

  /**
   * Sets whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   *
   * @param iisDisabled whether the controller is disabled
   */
  void flipDisable(bool iisDisabled) override;

  /**
   * Returns whether the controller is currently disabled.
   *
   * @return whether the controller is currently disabled
   */
  bool isDisabled() const override;

  /**
   * Blocks the current task until the controller has settled. Determining what settling means is
   * implementation-dependent.
   */
  void waitUntilSettled() override;

  /**
   * Writes the value of the controller output. This method might be automatically called in another
   * thread by the controller. The range of input values is expected to be [-1, 1].
   *
   * @param ivalue the controller's output in the range [-1, 1]
   */
  void controllerSet(double ivalue) override;

  protected:
  std::shared_ptr<Logger> logger;
  TimeUtil timeUtil;
  std::shared_ptr<AbstractMotor> motor;
  AbstractMotor::GearsetRatioPair pair;
  std::int32_t maxVelocity;
  double lastTarget = 0;
  bool controllerIsDisabled = false;
  bool hasFirstTarget = false;
  std::unique_ptr<SettledUtil> settledUtil;

  virtual void resumeMovement();
};
} // namespace okapi
