#include "IntakeWithJoystickCmd.h"
#include "OI.H"
#include <iostream>

IntakeWithJoystickCmd::IntakeWithJoystickCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void IntakeWithJoystickCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void IntakeWithJoystickCmd::Execute() {
	std::shared_ptr<frc::Joystick> operatorJoystick = oi->getOperatorController();
	intakeSub->isBoxIn();
	double horizontalStick = operatorJoystick->GetX();
	double verticalStick = operatorJoystick->GetY();

	if (horizontalStick > 0.6){
		intakeSub->intake(-horizontalStick/2.0, horizontalStick);
	} else if (horizontalStick < -0.6){
		intakeSub->intake(-horizontalStick, horizontalStick/2.0);
	} else {
		intakeSub->intake(pow(verticalStick,3));
		if(verticalStick<-0.1){
			intakeSub->setJawsOnSpring();
		}

	}
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeWithJoystickCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void IntakeWithJoystickCmd::End() {
	intakeSub->intake(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeWithJoystickCmd::Interrupted() {
	End();
}
