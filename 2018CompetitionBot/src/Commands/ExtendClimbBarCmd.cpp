/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ExtendClimbBarCmd.h"

ExtendClimbBarCmd::ExtendClimbBarCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void ExtendClimbBarCmd::Initialize() {
	elevatorSub->extendClimbBar();

}

// Called repeatedly when this Command is scheduled to run
void ExtendClimbBarCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ExtendClimbBarCmd::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ExtendClimbBarCmd::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendClimbBarCmd::Interrupted() {
	End();
}
