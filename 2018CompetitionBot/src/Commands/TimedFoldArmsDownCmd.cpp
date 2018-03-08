
#include "TimedFoldArmsDownCmd.h"

TimedFoldArmsDownCmd::TimedFoldArmsDownCmd(double time) {
	Requires(intakeSub.get());
	timeFolding = time;
}

// Called just before this Command runs the first time
void TimedFoldArmsDownCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TimedFoldArmsDownCmd::Execute() {
	intakeSub->foldArms(-1.0);

}

// Make this return true when this Command no longer needs to run execute()
bool TimedFoldArmsDownCmd::IsFinished() {
	if (TimeSinceInitialized() > timeFolding){
			return true;
	}
	return false;
}

// Called once after isFinished returns true
void TimedFoldArmsDownCmd::End() {
	intakeSub->foldArms(0.0);


}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedFoldArmsDownCmd::Interrupted() {
	End();
}
