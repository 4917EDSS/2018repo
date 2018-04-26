#include <iostream>
#include "ElevatorSub.h"
#include "../RobotMap.h"
#include "Commands/ElevatorWithJoystickCmd.h"
#include "Components/LinearInterpolation.h"
#include <Components/Logging/Log.h>

constexpr float ELEVATOR_POSITION_TOLERANCE = 5.0;
constexpr float LIFT_P = 1;
constexpr float LIFT_I = 0;
constexpr float LIFT_D = 0;
constexpr float LIFT_TOLERANCE = 1;
constexpr double SCALE_HEIGHT_SUDDEN_CHANGE_TOLERANCE = 400;
constexpr double RANGE_MAX_VALUE = 2000;
constexpr double RANGE_MIN_VALUE = 30;

ElevatorSub::ElevatorSub() : Subsystem("ElevatorSub") {
	elevatorMotor1.reset(new WPI_TalonSRX(ELEVATOR_MOTOR1_CANID));
	elevatorMotor1->SetName("Elevator", "Motor1");

	elevatorMotor2.reset(new WPI_TalonSRX(ELEVATOR_MOTOR2_CANID));
	elevatorMotor2->SetName("Elevator", "Motor2");
	//Make victor!!!!!!!!
	elevatorMotor3.reset(new WPI_VictorSPX(ELEVATOR_MOTOR3_CANID));
	elevatorMotor3->SetName("Elevator", "Motor3");
	//Make victor!!!!!!!!
	elevatorMotor4.reset(new WPI_VictorSPX(ELEVATOR_MOTOR4_CANID));
	elevatorMotor4->SetName("Elevator", "Motor4");

	elevatorMotorEnc.reset(new frc::Encoder(ELEVATOR_MOTOR_ENC1_DIO, ELEVATOR_MOTOR_ENC2_DIO));
	elevatorMotorEnc->SetName("Elevator", "Motor Enc");

	lowerLimit.reset(new DigitalInput(ELEVATOR_LOWER_LIMIT_DIO));
	lowerLimit->SetName("Elevator", "Lower Limit");

	rangefinder.reset(new frc::Ultrasonic(ELEVATOR_LIDAR_TRIG_DIO, ELEVATOR_LIDAR_ECHO_DIO, frc::Ultrasonic::kMilliMeters));
	rangefinder->SetName("Elevator", "Rangefinder");
	rangefinder->SetAutomaticMode(false);

	climbBarSolenoid.reset(new frc::Solenoid(CLIMB_BAR_PCM_ID));
	climbBarSolenoid->SetName("Elevator", "ClimbBar Deploy Solenoid");
	climbBarSolenoid->Set(false);


	climbBarInSolenoid.reset(new frc::Solenoid(CLIMB_BAR_IN_PCM_ID));
	climbBarInSolenoid->SetName("Elevator", "ClimbBar Retract Solenoid");
	climbBarInSolenoid->Set(false);

	target = 0;
	lastLidarValue = -1.0;
	isDoneFirstRangefinder = false;
	lastRangefinderValue = 0.0;

//	std::vector<DataPoints> table = {{100, 8}, {1000, 12}, {2000, 18}, {4000, 40}, {6000, 80}};
//	LinearInterpolation4917 encoderHeightTable(table);	// where x = encoder value and y = height in inches
}

void ElevatorSub::init() {
	climbBarSolenoid->Set(false);
	climbBarInSolenoid->Set(false);
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
			getFilteredRangefinderValue()
			);

	// Can add additional or easier-to-read periodic logging here
	//	logger.send(logger.PERIODIC, "$Rangefinder = %f\n", rangefinder->GetRangeMM() );
	return;
}
void ElevatorSub::updateSensorsPeriodic() {
	if (!isDoneFirstRangefinder){
		rangefinder->Ping();
		isDoneFirstRangefinder = true;
	}

	if (rangefinder->IsRangeValid()){
		storeNewRangefinderValue(rangefinder->GetRangeMM());
		rangefinder->Ping();
	}

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
bool ElevatorSub::atScaleHeight(){
	double currentLidarValue = getRangfinderDist();
	if (lastLidarValue - currentLidarValue >= SCALE_HEIGHT_SUDDEN_CHANGE_TOLERANCE){
	return true;
	}
	lastLidarValue = currentLidarValue;
	return false;
}

void ElevatorSub::startRangefinder(){
	rangefinder->SetAutomaticMode(true);
	lastLidarValue = getRangfinderDist();
}

double ElevatorSub::getRangfinderDist(){
	return rangefinder->GetRangeMM();
}

void ElevatorSub::stopRangefinder(){
	rangefinder->SetAutomaticMode(false);
}

bool ElevatorSub::isAtMaxDropHeight(){
	if (getElevatorEncoder() >= SCALE_BOX_HIGH_HEIGHT){
		return true;
	}

	return false;
}

void ElevatorSub::setElevatorMotorRaw(double speed){
	elevatorMotor1->Set(ControlMode::PercentOutput, speed);
	elevatorMotor2->Set(ControlMode::PercentOutput, speed);
	elevatorMotor3->Set(ControlMode::PercentOutput, speed);
	elevatorMotor4->Set(ControlMode::PercentOutput, speed);
	//std::cout<<speed<<std::endl;//get rid of this
}

void ElevatorSub::setElevatorMotor(double speed){

	if (isElevatorDown() && speed < 0){
		speed = 0;
		//resetElevatorEncoder();
	}
	else if (getElevatorEncoder() < 20 && speed < 0){
		speed = std::max(speed, -0.18);
	}
	else if (getElevatorEncoder() < 120 && speed < 0){
		speed = std::max(speed, -0.3);
	}
	else if (getElevatorEncoder() > MAX_ELEVATOR_HEIGHT - 35 && speed > 0){
		speed = std::min(speed, 0.3);
	}
	else if (speed < -0.6){
		if (elevatorMotorEnc->GetRate() < -150){
			speed = std::max(speed, -0.75);
		}
		else{
			speed = -0.6;
		}
	}
	else if (speed > 0.9){
		speed = 0.9;
	}



	setElevatorMotorRaw(speed);
}

bool ElevatorSub::isElevatorDown() {
	return !lowerLimit->Get() && getElevatorEncoder() < 20;
}

double ElevatorSub::getElevatorEncoder() {
	return elevatorMotorEnc->GetDistance();
}

void ElevatorSub::resetElevatorEncoder() {
	elevatorMotorEnc->Reset();
}

void ElevatorSub::setTarget(double newTarget) {
	target = newTarget;
}

void ElevatorSub::update(){
	setElevatorMotor((target - getElevatorEncoder()) * 0.01);
}

double ElevatorSub::convertHeightToEncoder(double cm){
	std::vector<DataPoints> table = {{0, 22}, {82.5, 40}, {154.75, 60}, {219, 80}, {335, 118}, {465.25, 160}, {523.75, 180}, {643.75, 220}};
	LinearInterpolation4917 encoderHeightTable(table);	// where x = encoder value and y = height in cm

	return encoderHeightTable.computeX(cm);
}

bool ElevatorSub::isFinishedMove(){
	if(fabs(target - getElevatorEncoder()) < ELEVATOR_POSITION_TOLERANCE && fabs(elevatorMotorEnc->GetRate()) < 45) {
		return true;
	} else {
		return false;
	}
}

void ElevatorSub::extendClimbBar() {
	climbBarInSolenoid->Set(false);
	climbBarSolenoid->Set(true);
}

void ElevatorSub::retractClimbBar(){
	climbBarSolenoid->Set(false);
	climbBarInSolenoid->Set(true);
}

void ElevatorSub::setClimbBarNeutral(){
	climbBarSolenoid->Set(false);
	climbBarInSolenoid->Set(false);

}

void ElevatorSub::storeNewRangefinderValue(double distance){
	if ((distance > RANGE_MIN_VALUE) && (distance < RANGE_MAX_VALUE)) {
		lastRangefinderValue = distance;
	}
	return;
}

double ElevatorSub::getFilteredRangefinderValue(){
	return lastRangefinderValue;
}
double ElevatorSub::getRawRangefinderValue(){
	return rangefinder->GetRangeMM();
}
