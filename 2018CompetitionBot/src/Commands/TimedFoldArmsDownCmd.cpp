
#include "TimedFoldArmsDownCmd.h"

TimedFoldArmsDownCmd::TimedFoldArmsDownCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void TimedFoldArmsDownCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TimedFoldArmsDownCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool TimedFoldArmsDownCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TimedFoldArmsDownCmd::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedFoldArmsDownCmd::Interrupted() {

}
