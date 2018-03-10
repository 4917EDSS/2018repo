/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/FoldArmsUpHeldCmd.h>
#include <iostream>

FoldArmsUpHeldCmd::FoldArmsUpHeldCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void FoldArmsUpHeldCmd::Initialize() {
	intakeSub->foldArms(1.0);
}

// Called repeatedly when this Command is scheduled to run
void FoldArmsUpHeldCmd::Execute() {
	if (intakeSub->isArmsUp()) {
		intakeSub->foldArms(0.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool FoldArmsUpHeldCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FoldArmsUpHeldCmd::End() {
	intakeSub->foldArms(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FoldArmsUpHeldCmd::Interrupted() {
	End();
}
