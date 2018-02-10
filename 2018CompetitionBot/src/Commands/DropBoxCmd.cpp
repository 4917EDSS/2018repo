#include "DropBoxCmd.h"
#include "iostream"
DropBoxCmd::DropBoxCmd() {
	// Use Requires() here to declare subsystem dependencies
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void DropBoxCmd::Initialize() {
	intakeSub->setOpen();
}

// Called repeatedly when this Command is scheduled to run
void DropBoxCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DropBoxCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DropBoxCmd::End() {
	intakeSub->setClose();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropBoxCmd::Interrupted() {

	End();
}

