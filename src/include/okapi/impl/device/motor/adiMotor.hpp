/*
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "api.h"
#include "okapi/api/control/controllerOutput.hpp"
#include "okapi/api/util/logging.hpp"

namespace okapi {
class ADIMotor : public ControllerOutput<double> {
  public:
  /**
   * A motor on the ADI ports.
   *
   * @param iport The ADI port number.
   * @param ireverse Whether the motor is reversed.
   * @param logger The logger that initialization warnings will be logged to.
   */
  ADIMotor(std::uint8_t iport,
           bool ireverse = false,
           const std::shared_ptr<Logger> &logger = Logger::getDefaultLogger());

  /**
   * Set the voltage to the motor.
   *
   * @param ivoltage voltage in the range [-127, 127].
   */
  virtual void moveVoltage(std::int8_t ivoltage) const;

  /**
   * Writes the value of the controller output. This method might be automatically called in another
   * thread by the controller. The range of input values is expected to be [-1, 1].
   *
   * @param ivalue the controller's output in the range [-1, 1]
   */
  void controllerSet(double ivalue) override;

  protected:
  const std::uint8_t port;
  const std::int8_t reversed;
};
} // namespace okapi
