/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/FoldArmsDownHeldCmd.h>

FoldArmsDownHeldCmd::FoldArmsDownHeldCmd() {
	Requires(intakeSub.get());
}

// Called just before this Command runs the first time
void FoldArmsDownHeldCmd::Initialize() {
	intakeSub->foldArms(-1.0);
}

// Called repeatedly when this Command is scheduled to run
void FoldArmsDownHeldCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool FoldArmsDownHeldCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FoldArmsDownHeldCmd::End() {
	intakeSub->foldArms(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FoldArmsDownHeldCmd::Interrupted() {
	End();
}
