#include "DriveTurnCmd.h"
#include <iostream>

DriveTurnCmd::DriveTurnCmd(double angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(drivetrainSub.get());
	turnDegrees = angle;
	lastMoveTime = 0;
}

// Called just before this Command runs the first time
void DriveTurnCmd::Initialize() {
	drivetrainSub->enableTurnPID(turnDegrees);
}

// Called repeatedly when this Command is scheduled to run
void DriveTurnCmd::Execute() {
	drivetrainSub->PIDTurn();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTurnCmd::IsFinished() {
	double timeFromLastMove = 0;
	if(fabs(drivetrainSub->getLeftEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE && fabs(drivetrainSub->getRightEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE){
		timeFromLastMove = TimeSinceInitialized() - lastMoveTime;
	} else {
		lastMoveTime = TimeSinceInitialized();
	}

	if((fabs(drivetrainSub->getRate()) < DRIVE_RATE_TOLERANCE && fabs(drivetrainSub->getAngle() - turnDegrees) < DRIVE_TURN_TOLERANCE) || (timeFromLastMove > 1)){
		return true;
	}
	else{
		std::cout << "GetRate" << drivetrainSub->getRate() << std::endl;
		std::cout << "GetAngle" << drivetrainSub->getAngle() << std::endl;
		return false;
	}
}

// Called once after isFinished returns true
void DriveTurnCmd::End() {
	drivetrainSub->disableTurnPID();
	drivetrainSub->drive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTurnCmd::Interrupted() {
	End();
}
