#include "ZeroElevatorCmd.h"

ZeroElevatorCmd::ZeroElevatorCmd() {
	Requires(elevatorSub.get());

}

// Called just before this Command runs the first time
void ZeroElevatorCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ZeroElevatorCmd::Execute() {
	elevatorSub->setElevatorMotor(-0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool ZeroElevatorCmd::IsFinished() {
	return elevatorSub->isElevatorDown();
}

// Called once after isFinished returns true
void ZeroElevatorCmd::End() {
	elevatorSub->setElevatorMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroElevatorCmd::Interrupted() {
	End();
}
