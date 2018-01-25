#include "RaiseRampCmd.h"

RaiseRampCmd::RaiseRampCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(liftSub.get());
}

// Called just before this Command runs the first time
void RaiseRampCmd::Initialize() {
	liftSub->raiseLift();
}

// Called repeatedly when this Command is scheduled to run
void RaiseRampCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseRampCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RaiseRampCmd::End() {
	liftSub->stopLift();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseRampCmd::Interrupted() {
	End();
}
