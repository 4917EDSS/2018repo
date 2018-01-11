#include "DrivetrainSub.h"
#include "../RobotMap.h"
#include "Commands/DriveWithJoystickCmd.h"


DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
  leftMotor1.reset(new TalonSRX(LEFT1_DRIVE_MOTOR_CANID));
  leftMotor2.reset(new TalonSRX(LEFT2_DRIVE_MOTOR_CANID));
  leftMotor3.reset(new TalonSRX(LEFT3_DRIVE_MOTOR_CANID));
  rightMotor1.reset(new TalonSRX(RIGHT1_DRIVE_MOTOR_CANID));
  rightMotor2.reset(new TalonSRX(RIGHT2_DRIVE_MOTOR_CANID));
  rightMotor3.reset(new TalonSRX(RIGHT3_DRIVE_MOTOR_CANID));
}

void DrivetrainSub::drive(double lSpeed, double rSpeed) {

 leftMotor1->Set(ControlMode::PercentOutput, -lSpeed);
 leftMotor2->Set(ControlMode::PercentOutput, -lSpeed);
 leftMotor3->Set(ControlMode::PercentOutput, -lSpeed);
 rightMotor1->Set(ControlMode::PercentOutput, rSpeed);
 rightMotor2->Set(ControlMode::PercentOutput, rSpeed);
 rightMotor3->Set(ControlMode::PercentOutput, rSpeed);
}

void DrivetrainSub::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCmd());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
