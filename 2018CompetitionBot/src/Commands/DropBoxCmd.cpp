#include "DropBoxCmd.h"
#include "iostream"
#include "OI.h"

DropBoxCmd::DropBoxCmd() {
	// Use Requires() here to declare subsystem dependencies
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void DropBoxCmd::Initialize() {
	intakeSub->setJawsOpen();
}

// Called repeatedly when this Command is scheduled to run
void DropBoxCmd::Execute() {
	std::shared_ptr<frc::Joystick> driverJoystick = oi->getDriverController();
	double leftStick = driverJoystick->GetY();
	if(leftStick > 0){
		intakeSub->intake(-0.35 * leftStick);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DropBoxCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DropBoxCmd::End() {
	intakeSub->setJawsOnSpring();
	intakeSub->intake(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropBoxCmd::Interrupted() {

	End();
}

