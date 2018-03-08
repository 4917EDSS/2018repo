/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "FoldArmsUpCmd.h"
#include <iostream>

FoldArmsUpCmd::FoldArmsUpCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void FoldArmsUpCmd::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void FoldArmsUpCmd::Execute() {
	intakeSub->foldArms(-1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool FoldArmsUpCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FoldArmsUpCmd::End() {
	intakeSub->foldArms(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FoldArmsUpCmd::Interrupted() {
	End();
}
