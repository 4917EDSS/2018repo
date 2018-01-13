#include "ElevatorSub.h"
#include "../RobotMap.h"

ElevatorSub::ElevatorSub() : Subsystem("ExampleSubsystem") {
	elevatorMotor.reset(new TalonSRX(ELEVATOR_MOTOR_CANID));
	elevatorMotorEnc.reset(new frc::Encoder(ELEVATOR_MOTOR_ENC1_DIO, ELEVATOR_MOTOR_ENC2_DIO));
}

void ElevatorSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ElevatorSub::setElevatorMotor(float speed){
	elevatorMotor->Set(ControlMode::PercentOutput,-speed);
}

double ElevatorSub::getElevatorEncoder() {
	return elevatorMotorEnc->GetDistance();
}
void ElevatorSub::resetElevatorEncoder() {
	elevatorMotorEnc->Reset();

}
