#include "ElevatorWithJoystickCmd.h"

ElevatorWithJoystickCmd::ElevatorWithJoystickCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void ElevatorWithJoystickCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorWithJoystickCmd::Execute() {

	std::shared_ptr<frc::Joystick> operatorJoystick = oi->getOperatorController();

	double verticalStick = operatorJoystick->GetRawAxis(OPERATOR_ELEVATOR_AXIS);
	verticalStick = pow(verticalStick, 3);
	elevatorSub->setElevatorMotor((-verticalStick) + 0.04);
	// WE SHOULDN"T SEND POSITIVE POWER AT BOTTOM
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorWithJoystickCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorWithJoystickCmd::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorWithJoystickCmd::Interrupted() {

}
