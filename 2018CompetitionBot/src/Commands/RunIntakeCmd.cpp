#include "RunIntakeCmd.h"
#include "OI.h"

RunIntakeCmd::RunIntakeCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void RunIntakeCmd::Initialize() {
	intakeSub->intake(1.0);
}

// Called repeatedly when this Command is scheduled to run
void RunIntakeCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RunIntakeCmd::IsFinished() {
	return intakeSub->IsLimitHit();
}

// Called once after isFinished returns true
void RunIntakeCmd::End() {
	intakeSub->intake(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunIntakeCmd::Interrupted() {
	End();
}
