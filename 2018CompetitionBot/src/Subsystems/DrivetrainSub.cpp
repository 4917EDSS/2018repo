#include "DrivetrainSub.h"
#include "../RobotMap.h"

DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
  leftMotor1.reset(new TalonSRX(LEFT1_DRIVE_MOTOR_CANID));
  leftMotor2.reset(new TalonSRX(LEFT2_DRIVE_MOTOR_CANID));
  leftMotor3.reset(new TalonSRX(LEFT3_DRIVE_MOTOR_CANID));
  rightMotor1.reset(new TalonSRX(RIGHT1_DRIVE_MOTOR_CANID));
  rightMotor2.reset(new TalonSRX(RIGHT2_DRIVE_MOTOR_CANID));
  rightMotor3.reset(new TalonSRX(RIGHT3_DRIVE_MOTOR_CANID));
}

void DrivetrainSub::drive(float lSpeed, float rSpeed) {

 leftMotor1->Set(-lSpeed);
 leftMotor2->Set(-lSpeed);
 leftMotor3->Set(-lSpeed);
 rightMotor1->Set(rSpeed);
 rightMotor2->Set(rSpeed);
 rightMotor3->set(rspeed);
}

void DrivetrainSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
