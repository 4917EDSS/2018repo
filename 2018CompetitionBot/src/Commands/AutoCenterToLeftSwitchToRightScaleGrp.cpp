/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoCenterToLeftSwitchToRightScaleGrp.h"
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/DelayedElevatorToHeightGrp.h"

AutoCenterToLeftSwitchToRightScaleGrp::AutoCenterToLeftSwitchToRightScaleGrp() {
	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1300}, std::vector<double> {-35, 10}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1630}, std::vector<double> {-10}));  //Took second box
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double>{600}, std::vector<double>{53}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-600, 1600}, std::vector<double> {-53, 5}));	//!

	AddSequential(new ReverseIntakeCmd(0.4));     //Dropped second box

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1150}, std::vector<double> {0}));
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {500, -3000}, std::vector<double> {40, -145})); // Backing off to right
}
