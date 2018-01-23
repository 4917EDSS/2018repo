#include <Commands/IntakeUntilDistanceCmd.h>
#include "Subsystems/IntakeSub.h"
#include "RobotMap.h"

IntakeUntilDistanceCmd::IntakeUntilDistanceCmd(double distance) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	targetDistance = distance;
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void IntakeUntilDistanceCmd::Initialize() {
	intakeSub->enableFrontUltrasonic(true);
	intakeSub->intake(0.5);
}

// Called repeatedly when this Command is scheduled to run
void IntakeUntilDistanceCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeUntilDistanceCmd::IsFinished() {
	if (intakeSub->getFrontUltrasonicDist() <= targetDistance){
		return true;
	}
	else {
		return false;
	}
}

// Called once after isFinished returns true
void IntakeUntilDistanceCmd::End() {
	intakeSub->intake(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeUntilDistanceCmd::Interrupted() {

}
