#ifndef DrivetrainSub_H
#define DrivetrainSub_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "Components/MotorBalancer.h"
#include "ctre/Phoenix.h"
#include "RobotMap.h"
#include "AHRS.h"

class DrivetrainSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

  std::shared_ptr<TalonSRX> leftMotor1;
  std::shared_ptr<TalonSRX> leftMotor2;
  std::shared_ptr<TalonSRX> leftMotor3;
  std::shared_ptr<TalonSRX> rightMotor1;
  std::shared_ptr<TalonSRX> rightMotor2;
  std::shared_ptr<TalonSRX> rightMotor3;
  std::shared_ptr<frc::Encoder> leftMotorEnc;
  std::shared_ptr<frc::Encoder> rightMotorEnc;
  std::shared_ptr<AHRS> gyro;
  std::shared_ptr<MotorBalancer> driveBalancer;
  std::shared_ptr<MotorBalancer> distanceBalancer;
  std::shared_ptr<frc::PIDController> driveBalancePID;
  std::shared_ptr<frc::PIDController> driveDistancePID;

  const float DRIVE_BALANCE_P = 1.0;
  const float DRIVE_BALANCE_I = 0.0;
  const float DRIVE_BALANCE_D = 0.0;
  const float DRIVE_DISTANCE_P = 1.0;
  const float DRIVE_DISTANCE_I = 0.0;
  const float DRIVE_DISTANCE_D = 0.0;


public:

  DrivetrainSub();
 double getLeftEncoder();
 double getRightEncoder();
 double getLeftEncoderSpeed();
 double getRightEncoderSpeed();
 void InitDefaultCommand();
 void drive( double lSpeed, double rSpeed );
 void disableBalancerPID();
 void disableDistancePID();
 void PIDDrive();
 void resetEncoders();
 void enableBalancerPID(float setPoint);
 void enableDistancePID(float speed, float setPoint);

};

#endif  // DrivetrainSub_H
