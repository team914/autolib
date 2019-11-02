/**
 * This file is heavily based off of 
 * okapi's chassisControllerBuilder
 */
#include "autolib/robot/robotBuilder.hpp"

namespace autolib{

RobotBuilder::RobotBuilder(const std::shared_ptr<Logger> &ilogger)
  : logger(ilogger) {
}

RobotBuilder &RobotBuilder::withMotors(const Motor &ileft,
                                                               const Motor &iright) {
  return withMotors(std::make_shared<Motor>(ileft), std::make_shared<Motor>(iright));
}

RobotBuilder &RobotBuilder::withMotors(const MotorGroup &ileft,
                                                               const MotorGroup &iright) {
  return withMotors(std::make_shared<MotorGroup>(ileft), std::make_shared<MotorGroup>(iright));
}

RobotBuilder &
RobotBuilder::withMotors(const std::shared_ptr<AbstractMotor> &ileft,
                                     const std::shared_ptr<AbstractMotor> &iright) {
  hasMotors = true;
  isSkidSteer = true;
  skidSteerMotors = {ileft, iright};

  if (!sensorsSetByUser) {
    leftSensor = ileft->getEncoder();
    rightSensor = iright->getEncoder();
  }

  if (!maxVelSetByUser) {
    maxVelocity = toUnderlyingType(ileft->getGearing());
  }

  if (!gearsetSetByUser) {
    gearset = ileft->getGearing();
  }

  return *this;
}

RobotBuilder &RobotBuilder::withMotors(const Motor &itopLeft,
                                                               const Motor &itopRight,
                                                               const Motor &ibottomRight,
                                                               const Motor &ibottomLeft) {
  return withMotors(std::make_shared<Motor>(itopLeft),
                    std::make_shared<Motor>(itopRight),
                    std::make_shared<Motor>(ibottomRight),
                    std::make_shared<Motor>(ibottomLeft));
}

RobotBuilder &RobotBuilder::withMotors(const MotorGroup &itopLeft,
                                                               const MotorGroup &itopRight,
                                                               const MotorGroup &ibottomRight,
                                                               const MotorGroup &ibottomLeft) {
  return withMotors(std::make_shared<MotorGroup>(itopLeft),
                    std::make_shared<MotorGroup>(itopRight),
                    std::make_shared<MotorGroup>(ibottomRight),
                    std::make_shared<MotorGroup>(ibottomLeft));
}

RobotBuilder &
RobotBuilder::withMotors(const std::shared_ptr<AbstractMotor> &itopLeft,
                                     const std::shared_ptr<AbstractMotor> &itopRight,
                                     const std::shared_ptr<AbstractMotor> &ibottomRight,
                                     const std::shared_ptr<AbstractMotor> &ibottomLeft) {
  hasMotors = true;
  isSkidSteer = false;
  xDriveMotors = {itopLeft, itopRight, ibottomRight, ibottomLeft};

  if (!sensorsSetByUser) {
    leftSensor = itopLeft->getEncoder();
    rightSensor = itopRight->getEncoder();
  }

  if (!maxVelSetByUser) {
    maxVelocity = toUnderlyingType(itopLeft->getGearing());
  }

  if (!gearsetSetByUser) {
    gearset = itopLeft->getGearing();
  }

  return *this;
}

RobotBuilder &RobotBuilder::withSensors(const ADIEncoder &ileft,
                                                                const ADIEncoder &iright) {
  return withSensors(std::make_shared<ADIEncoder>(ileft), std::make_shared<ADIEncoder>(iright));
}

RobotBuilder &RobotBuilder::withSensors(const okapi::ADIEncoder &ileft,
                                                                const okapi::ADIEncoder &iright,
                                                                const okapi::ADIEncoder &imiddle) {
  return withSensors(std::make_shared<ADIEncoder>(ileft),
                     std::make_shared<ADIEncoder>(iright),
                     std::make_shared<ADIEncoder>(imiddle));
}

RobotBuilder &RobotBuilder::withSensors(const IntegratedEncoder &ileft,
                                                                const IntegratedEncoder &iright) {
  return withSensors(std::make_shared<IntegratedEncoder>(ileft),
                     std::make_shared<IntegratedEncoder>(iright));
}

RobotBuilder &
RobotBuilder::withSensors(const okapi::IntegratedEncoder &ileft,
                                      const okapi::IntegratedEncoder &iright,
                                      const okapi::ADIEncoder &imiddle) {
  return withSensors(std::make_shared<IntegratedEncoder>(ileft),
                     std::make_shared<IntegratedEncoder>(iright),
                     std::make_shared<ADIEncoder>(imiddle));
}

RobotBuilder &
RobotBuilder::withSensors(const std::shared_ptr<ContinuousRotarySensor> &ileft,
                                      const std::shared_ptr<ContinuousRotarySensor> &iright) {
  sensorsSetByUser = true;
  leftSensor = ileft;
  rightSensor = iright;
  return *this;
}

RobotBuilder &RobotBuilder::withSensors(
  const std::shared_ptr<okapi::ContinuousRotarySensor> &ileft,
  const std::shared_ptr<okapi::ContinuousRotarySensor> &iright,
  const std::shared_ptr<okapi::ContinuousRotarySensor> &imiddle) {
  sensorsSetByUser = true;
  leftSensor = ileft;
  rightSensor = iright;
  middleSensor = imiddle;
  return *this;
}

RobotBuilder &
RobotBuilder::withGains(const IterativePosPIDController::Gains &idistanceGains,
                                    const IterativePosPIDController::Gains &iturnGains) {
  return withGains(idistanceGains, iturnGains, iturnGains);
}

RobotBuilder &
RobotBuilder::withGains(const IterativePosPIDController::Gains &idistanceGains,
                                    const IterativePosPIDController::Gains &iturnGains,
                                    const IterativePosPIDController::Gains &iangleGains) {
  hasGains = true;
  distanceGains = idistanceGains;
  turnGains = iturnGains;
  angleGains = iangleGains;
  return *this;
}

RobotBuilder &
RobotBuilder::withDerivativeFilters(std::unique_ptr<Filter> idistanceFilter,
                                                std::unique_ptr<Filter> iturnFilter,
                                                std::unique_ptr<Filter> iangleFilter) {
  distanceFilter = std::move(idistanceFilter);
  turnFilter = std::move(iturnFilter);
  angleFilter = std::move(iangleFilter);
  return *this;
}

RobotBuilder &RobotBuilder::withOdometry(const StateMode &imode,
                                                                 const QLength &imoveThreshold,
                                                                 const QAngle &iturnThreshold,
                                                                 const QSpeed &iwheelVelDelta) {
  hasOdom = true;
  odometry = nullptr;
  stateMode = imode;
  moveThreshold = imoveThreshold;
  turnThreshold = iturnThreshold;
  wheelVelDelta = iwheelVelDelta;
  return *this;
}

RobotBuilder &
RobotBuilder::withOdometry(std::unique_ptr<Odometry> iodometry,
                                       const StateMode &imode,
                                       const QLength &imoveThreshold,
                                       const QAngle &iturnThreshold) {
  if (iodometry == nullptr) {
    LOG_ERROR(std::string("RobotBuilder: Odometry cannot be null."));
    throw std::runtime_error("RobotBuilder: Odometry cannot be null.");
  }

  hasOdom = true;
  odometry = std::move(iodometry);
  stateMode = imode;
  moveThreshold = imoveThreshold;
  turnThreshold = iturnThreshold;
  return *this;
}

RobotBuilder &
RobotBuilder::withGearset(const AbstractMotor::GearsetRatioPair &igearset) {
  gearsetSetByUser = true;
  gearset = igearset;

  if (!maxVelSetByUser) {
    maxVelocity = toUnderlyingType(igearset.internalGearset);
  }

  return *this;
}

RobotBuilder &RobotBuilder::withDimensions(const ChassisScales &iscales) {
  scales = iscales;
  return *this;
}

RobotBuilder &RobotBuilder::withMaxVelocity(const double imaxVelocity) {
  maxVelSetByUser = true;
  maxVelocity = imaxVelocity;
  return *this;
}

RobotBuilder &RobotBuilder::withMaxVoltage(const double imaxVoltage) {
  maxVoltage = imaxVoltage;
  return *this;
}

RobotBuilder &RobotBuilder::withChassisControllerTimeUtilFactory(
  const TimeUtilFactory &itimeUtilFactory) {
  chassisControllerTimeUtilFactory = itimeUtilFactory;
  return *this;
}

RobotBuilder &RobotBuilder::withClosedLoopControllerTimeUtilFactory(
  const TimeUtilFactory &itimeUtilFactory) {
  closedLoopControllerTimeUtilFactory = itimeUtilFactory;
  return *this;
}

RobotBuilder &
RobotBuilder::withOdometryTimeUtilFactory(const TimeUtilFactory &itimeUtilFactory) {
  odometryTimeUtilFactory = itimeUtilFactory;
  return *this;
}

RobotBuilder &
RobotBuilder::withLogger(const std::shared_ptr<Logger> &ilogger) {
  controllerLogger = ilogger;
  return *this;
}

std::shared_ptr<DriveController> RobotBuilder::build(){
    return std::make_shared<DriveController>( buildController() );
}

std::shared_ptr<DriveController> RobotBuilder::buildOdometry() {
  if (!hasOdom) {
    std::string msg("RobotBuilder: No odometry information given.");
    LOG_ERROR(msg);
    throw std::runtime_error(msg);
  }

  return std::make_shared<DriveController>( buildDOCC( buildController() ) );
}

std::shared_ptr<ChassisController> RobotBuilder::buildController() {
  if (!hasMotors) {
    std::string msg("RobotBuilder: No motors given.");
    LOG_ERROR(msg);
    throw std::runtime_error(msg);
  }

  if (!gearsetSetByUser) {
    LOG_WARN(std::string(
      "RobotBuilder: The default gearset is selected. This could be a bug."));
  }

  std::int32_t calculatedTPR = gearsetToTPR(gearset.internalGearset) * gearset.ratio;
  if (calculatedTPR != scales.tpr) {
    LOG_WARN("RobotBuilder: The calculated TPR from the given gearset and ratio (" +
             std::to_string(calculatedTPR) +
             ") does not equal the TPR given in the ChassisScales (" + std::to_string(scales.tpr) +
             "). This is probably a bug.");
  }

  std::shared_ptr<ChassisController> out;

  if (hasGains) {
    out = buildCCPID();
  } else {
    out = buildCCI();
  }

  // Delay so the encoders don't return erroneous values
  pros::delay(30);

  return out;
}

std::shared_ptr<DefaultOdomChassisController>
RobotBuilder::buildDOCC(std::shared_ptr<ChassisController> chassisController) {
  if (isSkidSteer) {
    if (odometry == nullptr) {
      if (middleSensor == nullptr) {
        odometry = std::make_unique<Odometry>(odometryTimeUtilFactory.create(),
                                              chassisController->getModel(),
                                              chassisController->getChassisScales(),
                                              wheelVelDelta,
                                              controllerLogger);
      } else {
        odometry = std::make_unique<ThreeEncoderOdometry>(odometryTimeUtilFactory.create(),
                                                          chassisController->getModel(),
                                                          chassisController->getChassisScales(),
                                                          wheelVelDelta,
                                                          controllerLogger);
      }
    }

    auto out =
      std::make_shared<DefaultOdomChassisController>(chassisControllerTimeUtilFactory.create(),
                                                     std::move(odometry),
                                                     chassisController,
                                                     stateMode,
                                                     moveThreshold,
                                                     turnThreshold,
                                                     controllerLogger);

    out->startOdomThread();
    out->getOdomThread()->notifyWhenDeletingRaw(pros::c::task_get_current());

    return out;
  } else {
    std::string msg("RobotBuilder: Odometry is only supported with skid-steer layout.");
    LOG_ERROR(msg);
    throw std::runtime_error(msg);
  }
}

std::shared_ptr<ChassisControllerPID> RobotBuilder::buildCCPID() {
  if (isSkidSteer) {
    auto out = std::make_shared<ChassisControllerPID>(
      chassisControllerTimeUtilFactory.create(),
      makeSkidSteerModel(),
      std::make_unique<IterativePosPIDController>(distanceGains,
                                                  closedLoopControllerTimeUtilFactory.create(),
                                                  std::move(distanceFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(turnGains,
                                                  closedLoopControllerTimeUtilFactory.create(),
                                                  std::move(turnFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(angleGains,
                                                  closedLoopControllerTimeUtilFactory.create(),
                                                  std::move(angleFilter),
                                                  controllerLogger),
      gearset,
      scales,
      controllerLogger);

    out->startThread();
    out->getThread()->notifyWhenDeletingRaw(pros::c::task_get_current());

    return out;
  } else {
    auto out = std::make_shared<ChassisControllerPID>(
      chassisControllerTimeUtilFactory.create(),
      makeXDriveModel(),
      std::make_unique<IterativePosPIDController>(distanceGains,
                                                  closedLoopControllerTimeUtilFactory.create(),
                                                  std::move(distanceFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(turnGains,
                                                  closedLoopControllerTimeUtilFactory.create(),
                                                  std::move(turnFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(angleGains,
                                                  closedLoopControllerTimeUtilFactory.create(),
                                                  std::move(angleFilter),
                                                  controllerLogger),
      gearset,
      scales,
      controllerLogger);

    out->startThread();
    out->getThread()->notifyWhenDeletingRaw(pros::c::task_get_current());

    return out;
  }
}

std::shared_ptr<ChassisControllerIntegrated> RobotBuilder::buildCCI() {
  if (isSkidSteer) {
    return std::make_shared<ChassisControllerIntegrated>(
      chassisControllerTimeUtilFactory.create(),
      makeSkidSteerModel(),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.left,
                                                     gearset,
                                                     maxVelocity,
                                                     closedLoopControllerTimeUtilFactory.create(),
                                                     controllerLogger),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.right,
                                                     gearset,
                                                     maxVelocity,
                                                     closedLoopControllerTimeUtilFactory.create(),
                                                     controllerLogger),
      gearset,
      scales,
      controllerLogger);
  } else {
    return std::make_shared<ChassisControllerIntegrated>(
      chassisControllerTimeUtilFactory.create(),
      makeXDriveModel(),
      std::make_unique<AsyncPosIntegratedController>(
        std::make_shared<MotorGroup>(
          std::initializer_list({xDriveMotors.topLeft, xDriveMotors.bottomLeft}), controllerLogger),
        gearset,
        maxVelocity,
        closedLoopControllerTimeUtilFactory.create(),
        controllerLogger),
      std::make_unique<AsyncPosIntegratedController>(
        std::make_shared<MotorGroup>(
          std::initializer_list({xDriveMotors.topRight, xDriveMotors.bottomRight}),
          controllerLogger),
        gearset,
        maxVelocity,
        closedLoopControllerTimeUtilFactory.create(),
        controllerLogger),
      gearset,
      scales,
      controllerLogger);
  }
}

std::shared_ptr<SkidSteerModel> RobotBuilder::makeSkidSteerModel() {
  if (middleSensor != nullptr) {
    return std::make_shared<ThreeEncoderSkidSteerModel>(skidSteerMotors.left,
                                                        skidSteerMotors.right,
                                                        leftSensor,
                                                        middleSensor,
                                                        rightSensor,
                                                        maxVelocity,
                                                        maxVoltage);
  } else {
    return std::make_shared<SkidSteerModel>(skidSteerMotors.left,
                                            skidSteerMotors.right,
                                            leftSensor,
                                            rightSensor,
                                            maxVelocity,
                                            maxVoltage);
  }
}

std::shared_ptr<XDriveModel> RobotBuilder::makeXDriveModel() {
  return std::make_shared<XDriveModel>(xDriveMotors.topLeft,
                                       xDriveMotors.topRight,
                                       xDriveMotors.bottomRight,
                                       xDriveMotors.bottomLeft,
                                       leftSensor,
                                       rightSensor,
                                       maxVelocity,
                                       maxVoltage);
}

}//autolib