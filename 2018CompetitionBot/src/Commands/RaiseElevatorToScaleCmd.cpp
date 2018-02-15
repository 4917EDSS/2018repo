#include "RaiseElevatorToScaleCmd.h"

RaiseElevatorToScaleCmd::RaiseElevatorToScaleCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void RaiseElevatorToScaleCmd::Initialize() {
	elevatorSub->startTinyLidar();
	elevatorSub->setElevatorMotor(1.0);
	// TO DO get an initial measurement, the initial measurement can be sonar off the back or lidar out the front.
}

// Called repeatedly when this Command is scheduled to run
void RaiseElevatorToScaleCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseElevatorToScaleCmd::IsFinished() {

	if (elevatorSub->isAtTop()) {
		return true;
	}
	//TO DO check for distance to tell us if we are at the scale.
	return false;
}

// Called once after isFinished returns true
void RaiseElevatorToScaleCmd::End() {
	elevatorSub->setElevatorMotor(0.0);
	elevatorSub->endTinyLidar();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseElevatorToScaleCmd::Interrupted() {

}
