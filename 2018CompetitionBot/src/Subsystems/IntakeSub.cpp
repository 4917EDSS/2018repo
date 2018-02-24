#include "IntakeSub.h"
#include "../RobotMap.h"
#include "Commands/IntakeWithJoystickCmd.h"
#include "iostream"

constexpr double BOX_IN_DISTANCE_MM = 270;
constexpr double BOX_AT_JAWS_DISTANCE_MM = 600;

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotorLeft.reset(new TalonSRX(INTAKE_MOTOR_LEFT_CANID));
	intakeMotorRight.reset(new TalonSRX(INTAKE_MOTOR_RIGHT_CANID));
	intakeLimit.reset(new DigitalInput(INTAKE_LIMIT_SWITCH_DIO));
	intakeDistance.reset(new AnalogInput(INTAKE_DISTANCE_AI));
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
	/*if(getBoxDistance() < BOX_IN_DISTANCE_MM || !intakeLimit->Get()){
		return true;
	} else {
		return false;
	}*/
}

bool IntakeSub::isBoxAtJaws() {
	if(getBoxDistance() < BOX_AT_JAWS_DISTANCE_MM){
		return true;
	} else {
		return false;
	}
}

// Change values if sensor is changed
constexpr double MAX_DISTANCE_VOLTAGE = 0.4;
constexpr double MIN_DISTANCE_VOLTAGE = 2.3;
constexpr double MAX_DISTANCE_MM = 800;
constexpr double MIN_DISTANCE_MM = 100;

// returns distance in mm
double IntakeSub::getBoxDistance() {
	// Analog infrared distance sensor
	// - Returns distance as a voltage
	// - Max distance is at the smallest voltage (MAX_DISTANCE_VOLTAGE)
	// - Min distance is at the largest voltage (MIN_DISTANCE_VOLTAGE)
	//
	// e.g For the Sharp GP2Y0A21YK0F, 10cm to 80cm = 2.3V to 0.4V
	//
	// To get current distance, find ratio between min and max voltage
	//   Dcurrent = Dmax - [ (Dmax - Dmin) * (Vcurrent - Vmin) / (Vmax - Vmin) ]
	return MAX_DISTANCE_MM -
			((MAX_DISTANCE_MM - MIN_DISTANCE_MM) *
			 (intakeDistance->GetVoltage() - MAX_DISTANCE_VOLTAGE) /
			 (MIN_DISTANCE_VOLTAGE - MAX_DISTANCE_VOLTAGE));
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
