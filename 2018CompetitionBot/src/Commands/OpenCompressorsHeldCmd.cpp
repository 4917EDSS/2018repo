#include "OpenCompressorsHeldCmd.h"

OpenCompressorsHeldCmd::OpenCompressorsHeldCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void OpenCompressorsHeldCmd::Initialize() {
	intakeSub->openCompressor();
}

// Called repeatedly when this Command is scheduled to run
void OpenCompressorsHeldCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool OpenCompressorsHeldCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OpenCompressorsHeldCmd::End() {
	intakeSub->closeCompressor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OpenCompressorsHeldCmd::Interrupted() {
	End();
}
