#include "IntakeSub.h"
#include "../RobotMap.h"
#include "Commands/IntakeWithJoystickCmd.h"
#include "iostream"

constexpr double BOX_IN_DISTANCE_MM = 270;
constexpr double BOX_AT_JAWS_DISTANCE_MM = 600;

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotorLeft.reset(new WPI_TalonSRX(INTAKE_MOTOR_LEFT_CANID));
	intakeMotorLeft->SetName("Intake", "Left Motor");

	intakeMotorRight.reset(new WPI_TalonSRX(INTAKE_MOTOR_RIGHT_CANID));
	intakeMotorRight->SetName("Intake", "Right Motor");

	armFolderMotor.reset(new WPI_TalonSRX(ARM_FOLDER_CANID));
	armFolderMotor->SetName("Intake", "Arm Folder Motor");

	intakeCloseLimit.reset(new DigitalInput(INTAKE_LIMIT_CLOSE_DIO));
	intakeCloseLimit->SetName("Intake", "Intake Close Limit");

	intakeFarLimit.reset(new DigitalInput(INTAKE_LIMIT_FAR_DIO));
	intakeFarLimit->SetName("Intake", "Intake Far Limit");

	intakeDistance.reset(new AnalogInput(INTAKE_DISTANCE_AI));
	intakeDistance->SetName("Intake", "Intake Distance");

	jawOpenSolenoid.reset(new frc::Solenoid(JAWS_OPEN_PCM_ID));
	jawOpenSolenoid->SetName("Intake", "Jaw-open Solenoid");

	jawCloseSolenoid.reset(new frc::Solenoid(JAWS_CLOSE_PCM_ID));
	jawCloseSolenoid->SetName("Intake", "Jaw-close Solenoid");
}

void IntakeSub::InitDefaultCommand() {
	SetDefaultCommand(new IntakeWithJoystickCmd());
}

void IntakeSub::logPeriodicValues() {
	// Prefix the line with "LP:" for log-periodic so we can filter on that
	// Use commas to separate fields to make it easy to import into a spreadsheet
	logger.send(logger.PERIODIC, "LP:Intake,"
			"Motor Percent,L,%f,R,%f,"
			"Motor Currents,L,%f,R,%f,"
			"Limit,Far,%d,Close,%d,Dist,%d,"
			"Solenoid,Open,%d,Close,%d,"
			"\n",
			intakeMotorLeft->GetMotorOutputPercent(), intakeMotorRight->GetMotorOutputPercent(),
			intakeMotorLeft->GetOutputCurrent(), intakeMotorRight->GetOutputCurrent(),
			intakeCloseLimit->Get() ? 1 : 0, intakeFarLimit->Get() ? 1 : 0, intakeDistance->GetValue(),
			jawOpenSolenoid->Get() ? 1 : 0, jawCloseSolenoid->Get() ? 1 : 0
			);

	// Can add additional or easier-to-read periodic logging here
	//	logger.send(logger.PERIODIC, "$Rangefinder = %f\n", rangefinder->GetRangeMM() );
	return;
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
	return !intakeCloseLimit->Get();
	/*if(getBoxDistance() < BOX_IN_DISTANCE_MM || !intakeLimit->Get()){
		return true;
	} else {
		return false;
	}*/
}

bool IntakeSub::isBoxAtJaws() {
	return !intakeFarLimit->Get();
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

void IntakeSub::foldArms(double speed){
	armFolderMotor->Set(ControlMode::PercentOutput, speed);
}
