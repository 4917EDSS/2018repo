#include "IntakeSub.h"
#include "../RobotMap.h"
#include "Commands/IntakeWithJoystickCmd.h"
#include "iostream"

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotorLeft.reset(new TalonSRX(INTAKE_MOTOR_LEFT_CANID));
	intakeMotorRight.reset(new TalonSRX(INTAKE_MOTOR_RIGHT_CANID));
	intakeLimit.reset(new DigitalInput(INTAKE_LIMIT_SWITCH_DIO));
	jaws.reset(new frc::Solenoid(JAWS_PCM_ID1));
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

void IntakeSub::setOpen() {
	jaws->Set(true);
}

void IntakeSub::setClose() {
	jaws->Set(false);
}
