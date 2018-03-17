
#include <Commands/FoldArmsUpCmd.h>

FoldArmsUpCmd::FoldArmsUpCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void FoldArmsUpCmd::Initialize() {
	intakeSub->foldArms(0.5);
}

// Called repeatedly when this Command is scheduled to run
void FoldArmsUpCmd::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool FoldArmsUpCmd::IsFinished() {
	return intakeSub->isArmsUp();
}

// Called once after isFinished returns true
void FoldArmsUpCmd::End() {
	intakeSub->foldArms(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FoldArmsUpCmd::Interrupted() {
	End();
}
