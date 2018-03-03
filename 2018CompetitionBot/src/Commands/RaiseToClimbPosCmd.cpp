/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/RaiseToClimbPosCmd.h>
#include "OI.h"

RaiseToClimbPosCmd::RaiseToClimbPosCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void RaiseToClimbPosCmd::Initialize() {
	intakeSub->setJawsOpen();
	intakeSub->foldArms(-1.0);
}

// Called repeatedly when this Command is scheduled to run
void RaiseToClimbPosCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseToClimbPosCmd::IsFinished() {
	if(TimeSinceInitialized() > 0.25) {
		return true;
	} else {
		return false;
	}

}

// Called once after isFinished returns true
void RaiseToClimbPosCmd::End() {
	intakeSub->foldArms(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseToClimbPosCmd::Interrupted() {
	End();
}
