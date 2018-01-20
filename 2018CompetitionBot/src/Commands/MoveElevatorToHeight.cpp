#include "MoveElevatorToHeight.h"

MoveElevatorToHeight::MoveElevatorToHeight() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void MoveElevatorToHeight::Initialize() {
	elevatorSub->enableLiftPID(1000);
}

// Called repeatedly when this Command is scheduled to run
void MoveElevatorToHeight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool MoveElevatorToHeight::IsFinished() {
	return elevatorSub->PIDLiftIsFinished();
}

// Called once after isFinished returns true
void MoveElevatorToHeight::End() {
	elevatorSub->disableLiftPID();
	elevatorSub->setElevatorMotor(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveElevatorToHeight::Interrupted() {
	End();
}
