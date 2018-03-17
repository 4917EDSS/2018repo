/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DelayedElevatorToHeightGrp.h"
#include "Commands/MoveElevatorToHeightCmd.h"

DelayedElevatorToHeightGrp::DelayedElevatorToHeightGrp(double initialHeight, double time, double finalHeight) {
	AddSequential(new MoveElevatorToHeightCmd(initialHeight));
	AddSequential(new WaitCommand (time));
	AddSequential(new MoveElevatorToHeightCmd(finalHeight));

}
DelayedElevatorToHeightGrp::DelayedElevatorToHeightGrp(double time, double finalHeight) {
	AddSequential(new WaitCommand (time));
	AddSequential(new MoveElevatorToHeightCmd(finalHeight));

}
