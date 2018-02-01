#include <Commands/MoveElevatorToHeightCmd.h>

MoveElevatorToHeightCmd::MoveElevatorToHeightCmd(double height) : height(height) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void MoveElevatorToHeightCmd::Initialize() {
	elevatorSub->enableLiftPID(height);
}

// Called repeatedly when this Command is scheduled to run
void MoveElevatorToHeightCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool MoveElevatorToHeightCmd::IsFinished() {
	return elevatorSub->PIDLiftIsFinished();
}

// Called once after isFinished returns true
void MoveElevatorToHeightCmd::End() {
	elevatorSub->disableLiftPID();
	elevatorSub->setElevatorMotor(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveElevatorToHeightCmd::Interrupted() {
	End();
}