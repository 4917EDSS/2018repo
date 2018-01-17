#include "ElevatorSub.h"
#include "../RobotMap.h"

ElevatorSub::ElevatorSub() : Subsystem("ExampleSubsystem") {
	//elevatorMotor.reset(new TalonSRX(ELEVATOR_MOTOR_CANID));
	elevatorMotorEnc.reset(new frc::Encoder(ELEVATOR_MOTOR_ENC1_DIO, ELEVATOR_MOTOR_ENC2_DIO));
	target = 0;
}

void ElevatorSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ElevatorSub::setElevatorMotor(float speed){
	//elevatorMotor->Set(ControlMode::PercentOutput,-speed);
}

double ElevatorSub::getElevatorEncoder() {
	return elevatorMotorEnc->GetDistance();
}

void ElevatorSub::resetElevatorEncoder() {
	elevatorMotorEnc->Reset();
}

void ElevatorSub::setTarget(int newTarget) {
	target = newTarget;
}

void ElevatorSub::update(){
	double currentPosition = getElevatorEncoder();
	if (currentPosition < target - ELEVATOR_POSITION_TOLERANCE){
		setElevatorMotor(1.0);
	}
	else if (currentPosition > target + ELEVATOR_POSITION_TOLERANCE){
		setElevatorMotor(-1.0);
	}
	else{
		setElevatorMotor(0.0);
	}
}


