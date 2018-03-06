#include <iostream>
#include "ElevatorSub.h"
#include "../RobotMap.h"
#include "Commands/ElevatorWithJoystickCmd.h"
#include "Components/LinearInterpolation.h"
#include <Components/Logging/Log.h>

constexpr float ELEVATOR_POSITION_TOLERANCE = 15.0;
constexpr float LIFT_P = 1;
constexpr float LIFT_I = 0;
constexpr float LIFT_D = 0;
constexpr float LIFT_TOLERANCE = 1;
constexpr double SCALE_HEIGHT_SUDDEN_CHANGE_TOLERANCE = 400;

ElevatorSub::ElevatorSub() : Subsystem("ElevatorSub") {
	elevatorMotor1.reset(new TalonSRX(ELEVATOR_MOTOR1_CANID));
	elevatorMotor2.reset(new TalonSRX(ELEVATOR_MOTOR2_CANID));
	elevatorMotorEnc.reset(new frc::Encoder(ELEVATOR_MOTOR_ENC1_DIO, ELEVATOR_MOTOR_ENC2_DIO));
//	liftPID.reset(new PIDController(LIFT_P, LIFT_I, LIFT_D, elevatorMotorEnc.get(), elevatorMotor1.get()));
	lowerLimit.reset(new DigitalInput(ELEVATOR_LOWER_LIMIT_DIO));
	rangefinder.reset(new frc::Ultrasonic(ELEVATOR_LIDAR_TRIG_DIO, ELEVATOR_LIDAR_ECHO_DIO, frc::Ultrasonic::kMilliMeters));
	rangefinder->SetAutomaticMode(true);

	target = 0;
	finishedMove = true;
	lastLidarValue = -1.0;

//	std::vector<DataPoints> table = {{100, 8}, {1000, 12}, {2000, 18}, {4000, 40}, {6000, 80}};
//	LinearInterpolation4917 encoderHeightTable(table);	// where x = encoder value and y = height in inches
}

void ElevatorSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ElevatorWithJoystickCmd());
}

void ElevatorSub::logPeriodicValues() {
	// Prefix the line with "LP:" for log-periodic so we can filter on that
	// Use commas to separate fields to make it easy to import into a spreadsheet
	logger.send(logger.PERIODIC, "%d,LP:Elevator,"
			"Motor Percent,#1,%f,#2,%f,"
			"Motor Currents,#1,%f,#2,%f,"
			"Motor Encoder,%d,Raw,%d,"
			"Lower Limit,%d,"
			"LIDAR Distance,%f,"
			"\n",
			(uint32_t)(frc::RobotController::GetFPGATime() & 0xFFFFFFFF),
			elevatorMotor1->GetMotorOutputPercent(), elevatorMotor2->GetMotorOutputPercent(),
			elevatorMotor1->GetOutputCurrent(), elevatorMotor2->GetOutputCurrent(),
			elevatorMotorEnc->Get(), elevatorMotorEnc->GetRaw(),
			lowerLimit->Get() ? 1 : 0,
			rangefinder->GetRangeMM()
			);

	// Can add additional or easier-to-read periodic logging here
	//	logger.send(logger.PERIODIC, "$Rangefinder = %f\n", rangefinder->GetRangeMM() );
	return;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
bool ElevatorSub::atScaleHeight(){
	double currentLidarValue = getLidarValue();
	if (lastLidarValue - currentLidarValue >= SCALE_HEIGHT_SUDDEN_CHANGE_TOLERANCE){
	return true;
	}
	lastLidarValue = currentLidarValue;
	return false;
}
void ElevatorSub::startTinyLidar(){
	rangefinder->SetAutomaticMode(true);
	lastLidarValue = getLidarValue();
}
double ElevatorSub::getLidarValue(){
	return rangefinder->GetRangeMM();
}
void ElevatorSub::endTinyLidar(){
	rangefinder->SetAutomaticMode(false);
}
bool ElevatorSub::isAtMaxDropHeight(){
	if (getElevatorEncoder() >= SCALE_BOX_HIGH_HEIGHT){
		return true;
	}

	return false;
}
void ElevatorSub::setElevatorMotorRaw(double speed){
	elevatorMotor1->Set(ControlMode::PercentOutput, -speed);
	elevatorMotor2->Set(ControlMode::PercentOutput, -speed);
}

void ElevatorSub::setElevatorMotor(double speed){
	if (isElevatorDown() && speed < 0){
		speed = 0;
		resetElevatorEncoder();
	}
	else if (getElevatorEncoder() < 50 && speed < 0){
		speed = std::max(speed, -0.25);
	}

	else if (getElevatorEncoder() > MAX_ELEVATOR_HEIGHT - 20 && speed > 0){
		speed = std::min(speed, 0.4);
	}
	setElevatorMotorRaw(speed);
}

bool ElevatorSub::isElevatorDown() {
	return lowerLimit->Get();
}

double ElevatorSub::getElevatorEncoder() {
	return elevatorMotorEnc->GetDistance();
}

void ElevatorSub::resetElevatorEncoder() {
	elevatorMotorEnc->Reset();
}

void ElevatorSub::setTarget(double newTarget) {
	target = newTarget;
	finishedMove = false;
}

void ElevatorSub::update(){
	if (!finishedMove) {
		double currentPosition = getElevatorEncoder();
		if (currentPosition < target - ELEVATOR_POSITION_TOLERANCE){
			setElevatorMotor(1.0);
		}
		else if (currentPosition > target + ELEVATOR_POSITION_TOLERANCE){
			setElevatorMotor(-1.0);
		}
		else{
			setElevatorMotor(0.0);
			finishedMove = true;
		}
	}
}

//void ElevatorSub::enableLiftPID(float setPoint){
//	std::cout<<"EnableLiftPID"<<std::endl;
//	Preferences *prefs = Preferences::GetInstance();
//	std::cout<<"EnableLiftPID - preferences"<<std::endl;
//	liftPID->SetPID(prefs->GetFloat("LiftP", LIFT_P), prefs->GetFloat("LiftI", LIFT_I), prefs->GetFloat("LiftD", LIFT_D));
//	std::cout<<"EnableLiftPID - setPID"<<std::endl;
//	liftPID->SetAbsoluteTolerance(prefs->GetFloat("LiftTolerance", LIFT_TOLERANCE));
//	std::cout<<"EnableLiftPID - setTol"<<std::endl;
//	liftPID->SetSetpoint(setPoint);
//	std::cout<<"EnableLiftPID - set point"<<std::endl;
//	liftPID->Enable();
//	std::cout<<"EnableLiftPID - enabled"<<std::endl;
//}
//
//void ElevatorSub::disableLiftPID(){
//	liftPID->Disable();
//}
//
//bool ElevatorSub::PIDLiftIsFinished(){
//	return liftPID->OnTarget();
//}

double ElevatorSub::convertHeightToEncoder(double cm){
	std::vector<DataPoints> table = {{0, 22}, {82.5, 40}, {154.75, 60}, {219, 80}, {335, 118}, {465.25, 160}, {523.75, 180}, {643.75, 220}};
	LinearInterpolation4917 encoderHeightTable(table);	// where x = encoder value and y = height in cm

	return encoderHeightTable.computeX(cm);
}
