#include "DeployRampCmd.h"

DeployRampCmd::DeployRampCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(liftSub.get());
}

// Called just before this Command runs the first time
void DeployRampCmd::Initialize() {
	liftSub->lowerRamp();
}

// Called repeatedly when this Command is scheduled to run
void DeployRampCmd::Execute() {
	// if the ramp is lowered and not fully extended
	if ((liftSub->isRampLowered()) && !(liftSub->isRampExtended())) {
		liftSub->extendRamp();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DeployRampCmd::IsFinished() {
	// if ramp is lowered and is fully extended
	if ((liftSub->isRampLowered()) && (liftSub->isRampExtended())) {
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void DeployRampCmd::End() {
	liftSub->stopRamp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployRampCmd::Interrupted() {
	End();
}
