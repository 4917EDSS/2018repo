#include "IntakeSub.h"
#include "../RobotMap.h"

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotor.reset(new TalonSRX(INTAKE_MOTOR_CANID));
	intakeLimit.reset(new DigitalInput(INTAKE_LIMIT_SWITCH_DIO));

//	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
//	lw->AddActuator("Intake", "Compressor Solenoid", compressors);
}
//
void IntakeSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void IntakeSub::intake(double speed) {
	intakeMotor->Set(ControlMode::PercentOutput, speed);
}

bool IntakeSub::IsLimitHit() {
	return !intakeLimit->Get();
}
