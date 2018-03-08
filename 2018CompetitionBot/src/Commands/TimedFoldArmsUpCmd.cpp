
#include "TimedFoldArmsUpCmd.h"

TimedFoldArmsUpCmd::TimedFoldArmsUpCmd(double time) {
	Requires(intakeSub.get());
	timeFolding = time;
}

// Called just before this Command runs the first time
void TimedFoldArmsUpCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TimedFoldArmsUpCmd::Execute() {
	intakeSub->foldArms(1.0);

}

// Make this return true when this Command no longer needs to run execute()
bool TimedFoldArmsUpCmd::IsFinished() {
	if (TimeSinceInitialized() > timeFolding){
			return true;
	}
	return false;
}

// Called once after isFinished returns true
void TimedFoldArmsUpCmd::End() {
	intakeSub->foldArms(0.0);


}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedFoldArmsUpCmd::Interrupted() {
	End();
}
