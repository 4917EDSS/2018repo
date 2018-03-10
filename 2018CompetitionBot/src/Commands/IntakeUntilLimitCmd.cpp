#include <Commands/IntakeUntilLimitCmd.h>
#include "Subsystems/IntakeSub.h"
#include "RobotMap.h"
#include "iostream"

IntakeUntilLimitCmd::IntakeUntilLimitCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void IntakeUntilLimitCmd::Initialize() {
	intakeSub->setJawsOpen();
	intakeSub->intake(1.0);
	jawsSetToSpring = false;
	lastMoveTime = 0;
}

// Called repeatedly when this Command is scheduled to run
void IntakeUntilLimitCmd::Execute() {
	double timeFromLastMove = 0;
	if(intakeSub->isBoxAtJaws()){
		timeFromLastMove = TimeSinceInitialized() - lastMoveTime;
		intakeSub->setJawsOnSpring();
		jawsSetToSpring = true;
	} else {
		lastMoveTime = TimeSinceInitialized();
	}

	if(timeFromLastMove > 1) {
		intakeSub->intake(1.0, -0.2);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeUntilLimitCmd::IsFinished() {
	return intakeSub->isBoxIn();
}

// Called once after isFinished returns true
void IntakeUntilLimitCmd::End() {
	intakeSub->setJawsClose();
	intakeSub->intake(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeUntilLimitCmd::Interrupted() {
	intakeSub->intake(0.0);
}
