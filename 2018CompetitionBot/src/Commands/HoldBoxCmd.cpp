#include "HoldBoxCmd.h"

HoldBoxCmd::HoldBoxCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void HoldBoxCmd::Initialize() {
	intakeSub->setJawsClose();
}

// Called repeatedly when this Command is scheduled to run
void HoldBoxCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool HoldBoxCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void HoldBoxCmd::End() {
	intakeSub->setJawsOnSpring();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HoldBoxCmd::Interrupted() {
	End();
}
