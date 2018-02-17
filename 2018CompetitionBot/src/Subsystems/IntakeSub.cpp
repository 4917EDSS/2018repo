#include "IntakeSub.h"
#include "../RobotMap.h"
#include "Commands/IntakeWithJoystickCmd.h"
#include "iostream"

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotorLeft.reset(new TalonSRX(INTAKE_MOTOR_LEFT_CANID));
	intakeMotorRight.reset(new TalonSRX(INTAKE_MOTOR_RIGHT_CANID));
	intakeLimit.reset(new DigitalInput(INTAKE_LIMIT_SWITCH_DIO));
	jawOpenSolenoid.reset(new frc::Solenoid(JAWS_OPEN_PCM_ID));
	jawCloseSolenoid.reset(new frc::Solenoid(JAWS_CLOSE_PCM_ID));

	//hcsr04.reset(new frc::Ultrasonic(INTAKE_ULTRASONIC_TRIG_DIO, INTAKE_ULTRASONIC_ECHO_DIO, frc::Ultrasonic::kMilliMeters));
}

void IntakeSub::InitDefaultCommand() {
	SetDefaultCommand(new IntakeWithJoystickCmd());
}

//Positive is expelling the box, Negative is intaking the box
void IntakeSub::intake(double speed) {
	intake(speed, speed);
}

void IntakeSub::intake(double leftSpeed, double rightSpeed) {
	intakeMotorLeft->Set(ControlMode::PercentOutput, -leftSpeed);
	intakeMotorRight->Set(ControlMode::PercentOutput, rightSpeed);
}

bool IntakeSub::isBoxIn() {

	return !intakeLimit->Get();
}

void IntakeSub::enableFrontUltrasonic(bool enable){
	//hcsr04->SetAutomaticMode(enable);
}

double IntakeSub::getFrontUltrasonicDist(){
	//return hcsr04->GetRangeMM();
	return 0.0;
}

void IntakeSub::setJawsOpen() {
	jawOpenSolenoid->Set(true);
	jawCloseSolenoid->Set(false);
}

void IntakeSub::setJawsClose() {
	jawOpenSolenoid->Set(false);
	jawCloseSolenoid->Set(true);
}

void IntakeSub::setJawsOnSpring() {
	jawOpenSolenoid->Set(false);
	jawCloseSolenoid->Set(false);
}
