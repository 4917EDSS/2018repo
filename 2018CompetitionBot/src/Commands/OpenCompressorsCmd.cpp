#include "OpenCompressorsCmd.h"

OpenCompressorsCmd::OpenCompressorsCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
	directionOpen = true;
}

OpenCompressorsCmd::OpenCompressorsCmd(bool open) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
	directionOpen = open;
}

// Called just before this Command runs the first time
void OpenCompressorsCmd::Initialize() {
	if(directionOpen) {
		intakeSub->openCompressor();
	} else {
		intakeSub->closeCompressor();
	}
}

// Called repeatedly when this Command is scheduled to run
void OpenCompressorsCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool OpenCompressorsCmd::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void OpenCompressorsCmd::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OpenCompressorsCmd::Interrupted() {
	End();
}
