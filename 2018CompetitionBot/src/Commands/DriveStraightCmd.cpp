#include "DriveStraightCmd.h"
#include <iostream>
#include <cmath>

DriveStraightCmd::DriveStraightCmd(int distance) {
	this->targetDistance = distance;
	Requires(drivetrainSub.get());
}

// Called just before this Command runs the first time
void DriveStraightCmd::Initialize() {
	drivetrainSub->resetEncoders();
	drivetrainSub->enableBalancerPID(0);
	drivetrainSub->enableDistancePID(0.7, targetDistance);
	timeFromLastMove = 0;
	lastMoveTime = 0;
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightCmd::Execute() {
	drivetrainSub->PIDDrive();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightCmd::IsFinished() {
	if(fabs(drivetrainSub->getLeftEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE && fabs(drivetrainSub->getRightEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE){
		timeFromLastMove = TimeSinceInitialized() - lastMoveTime;
	} else {
		lastMoveTime = TimeSinceInitialized();
	}

	if((fabs(drivetrainSub->getLeftEncoder()-targetDistance)<=DRIVE_DISTANCE_TOLERANCE && fabs(drivetrainSub->getLeftEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE) || (timeFromLastMove > 1)){
		return true;
	}
	else{
		return false;
	}
}

// Called once after isFinished returns true
void DriveStraightCmd::End() {
	drivetrainSub->disableBalancerPID();
	drivetrainSub->disableDistancePID();
	drivetrainSub->drive(0.0, 0.0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightCmd::Interrupted() {
	End();
}
