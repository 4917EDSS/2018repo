#include "LiftSub.h"
#include "../RobotMap.h"

LiftSub::LiftSub() : Subsystem("ExampleSubsystem") {
	rampMotor1.reset(new TalonSRX(RAMP1_MOTOR_CANID));
	rampMotor2.reset(new TalonSRX(RAMP2_MOTOR_CANID));
	liftMotor1.reset(new TalonSRX(LIFT1_MOTOR_CANID));
	rampLimit.reset(new DigitalInput(RAMP_LOWER_LIMIT_SWITCH_DIO));
	extentionLimit.reset(new DigitalInput(RAMP_EXTENSION_LIMIT_SWITCH_DIO));
}

void LiftSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void LiftSub::lowerRamp() {
	rampMotor1->Set(ControlMode::PercentOutput,1.0);
	rampMotor2->Set(ControlMode::PercentOutput,0.5); // starts extending ramp half speed
}

void LiftSub::extendRamp() {
	rampMotor1->Set(ControlMode::PercentOutput,0.0);
	rampMotor2->Set(ControlMode::PercentOutput,1.0);
}

void LiftSub::raiseLift() {
	liftMotor1->Set(ControlMode::PercentOutput,1.0);
}

void LiftSub::stopRamp() { // stops all ramp motors
	rampMotor1->Set(ControlMode::PercentOutput,0.0);
	rampMotor2->Set(ControlMode::PercentOutput,0.0);
}

void LiftSub::stopLift() { // stops all lift motors
	liftMotor1->Set(ControlMode::PercentOutput,0.0);
}

bool LiftSub::isRampLowered() {
	return !rampLimit->Get();
}

bool LiftSub::isRampExtended() {
	return !extentionLimit->Get();
}
