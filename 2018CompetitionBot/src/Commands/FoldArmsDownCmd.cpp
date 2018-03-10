
#include <Commands/FoldArmsDownCmd.h>

FoldArmsDownCmd::FoldArmsDownCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void FoldArmsDownCmd::Initialize() {
	intakeSub->foldArms(-1.0);
}

// Called repeatedly when this Command is scheduled to run
void FoldArmsDownCmd::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool FoldArmsDownCmd::IsFinished() {
	return intakeSub->isArmsDown();
}

// Called once after isFinished returns true
void FoldArmsDownCmd::End() {
	intakeSub->foldArms(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FoldArmsDownCmd::Interrupted() {
	End();
}
