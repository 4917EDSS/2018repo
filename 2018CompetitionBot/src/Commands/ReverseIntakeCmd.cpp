#include "ReverseIntakeCmd.h"

ReverseIntakeCmd::ReverseIntakeCmd(double time) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
	timeExpelling = time;
}

// Called just before this Command runs the first time
void ReverseIntakeCmd::Initialize() {
	intakeSub->intake(-1.0);
	intakeSub->setJawsOnSpring();
}

// Called repeatedly when this Command is scheduled to run
void ReverseIntakeCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ReverseIntakeCmd::IsFinished() {
	if(TimeSinceInitialized() > timeExpelling){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ReverseIntakeCmd::End() {
	intakeSub->intake(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReverseIntakeCmd::Interrupted() {
	End();
}
