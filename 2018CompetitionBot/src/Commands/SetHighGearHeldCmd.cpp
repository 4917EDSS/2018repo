#include <Commands/SetHighGearHeldCmd.h>
#include "Subsystems/DriveTrainSub.h"

SetHighGearHeldCmd::SetHighGearHeldCmd() {
	// Requiring this does not allow us to drive with joystick command
	// Requires(drivetrainSub.get());
}

// Called just before this Command runs the first time
void SetHighGearHeldCmd::Initialize() {
	drivetrainSub->setHighGear();
}

// Called repeatedly when this Command is scheduled to run
void SetHighGearHeldCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SetHighGearHeldCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetHighGearHeldCmd::End() {
	drivetrainSub->setLowGear();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetHighGearHeldCmd::Interrupted() {
	End();
}
