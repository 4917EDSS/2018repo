#include "DriveUntilDistanceCmd.h"
#include "Subsystems/DrivetrainSub.h"
#include "RobotMap.h"

DriveUntilDistanceCmd::DriveUntilDistanceCmd(double distance) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	targetDistance = distance;
	Requires(drivetrainSub.get());
}

// Called just before this Command runs the first time
void DriveUntilDistanceCmd::Initialize() {
	drivetrainSub->enableFrontUltrasonic(true);
	drivetrainSub->drive(0.5, 0.5);
}

// Called repeatedly when this Command is scheduled to run
void DriveUntilDistanceCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DriveUntilDistanceCmd::IsFinished() {
	if (drivetrainSub->getFrontUltrasonicDist() <= targetDistance){
		return true;
	}
	else {
		return false;
	}
}

// Called once after isFinished returns true
void DriveUntilDistanceCmd::End() {
	drivetrainSub->drive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveUntilDistanceCmd::Interrupted() {

}
