#include <iostream>
#include "ElevatorSub.h"
#include "../RobotMap.h"
#include "Commands/ElevatorWithJoystickCmd.h"
#include "Components/LinearInterpolation.h"
#include <Components/Logging/Log.h>

constexpr float LIFT_P = 1;
constexpr float LIFT_I = 0;
constexpr float LIFT_D = 0;
const float LIFT_TOLERANCE = 1;

ElevatorSub::ElevatorSub() : Subsystem("ElevatorSub") {
	elevatorMotor1.reset(new TalonSRX(ELEVATOR_MOTOR1_CANID));
	elevatorMotor2.reset(new TalonSRX(ELEVATOR_MOTOR2_CANID));
	elevatorMotorEnc.reset(new frc::Encoder(ELEVATOR_MOTOR_ENC1_DIO, ELEVATOR_MOTOR_ENC2_DIO));
//	liftPID.reset(new PIDController(LIFT_P, LIFT_I, LIFT_D, elevatorMotorEnc.get(), elevatorMotor1.get()));
	lowerLimit.reset(new DigitalInput(ELEVATOR_LOWER_LIMIT_DIO));
	target = 0;
	finishedMove = true;

//	std::vector<DataPoints> table = {{100, 8}, {1000, 12}, {2000, 18}, {4000, 40}, {6000, 80}};
//	LinearInterpolation4917 encoderHeightTable(table);	// where x = encoder value and y = height in inches
}

void ElevatorSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ElevatorWithJoystickCmd());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ElevatorSub::setElevatorMotor(float speed){
	if (isElevatorDown() && speed < 0){
		speed = 0;
		resetElevatorEncoder();
	}
	elevatorMotor1->Set(ControlMode::PercentOutput, -speed);
	elevatorMotor2->Set(ControlMode::PercentOutput, -speed);
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

void ElevatorSub::setTarget(int newTarget) {
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
