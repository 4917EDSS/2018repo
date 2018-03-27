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
	// Add Commands here:
		// e.g. AddSequential(new Command1());
		//      AddSequential(new Command2());
		// these will run in order.

		AddParallel (new FoldArmsDownCmd());
		AddSequential(new ZeroElevatorCmd());

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1300}, std::vector<double> {-35, 10}));

		AddSequential(new ReverseIntakeCmd(0.4));

		AddParallel(new ZeroElevatorCmd());

		AddSequential(new SilkyMotionCmd(std::vector<double> {-1000,-1000}, std::vector<double> {-20,45}));  //Took second box

		AddParallel(new IntakeUntilLimitCmd());
		AddSequential(new SilkyMotionCmd(std::vector<double>{1000}, std::vector<double>{0}));

		AddParallel(new DelayedElevatorToHeightGrp(ElevatorSub::CARRY_HEIGHT, 3,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {-3000, -2500, -800, 1200}, std::vector<double> {180, 0, 30, 50}));  //Took second box

		AddSequential(new ReverseIntakeCmd(0.4));
}
