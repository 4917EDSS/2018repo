#include "IntakeSub.h"
#include "../RobotMap.h"

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotor.reset(new TalonSRX(INTAKE_MOTOR_CANID));
}

void IntakeSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void IntakeSub::intake(double speed) {
	intakeMotor->Set(ControlMode::PercentOutput, speed);
}
