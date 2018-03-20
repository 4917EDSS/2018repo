/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/FoldArmsDownCmd.h>
#include "AutoRightToLeftScaleToLeftSwitchGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Subsystems/IntakeSub.h"

AutoRightToLeftScaleToLeftSwitchGrp::AutoRightToLeftScaleToLeftSwitchGrp() {
	AddParallel (new FoldArmsDownCmd());
	AddParallel(new DelayedElevatorToHeightGrp(ElevatorSub::CARRY_HEIGHT,4.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {4210, 2300, 3340, 1300}, std::vector<double> {0, -90, 0, 120}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new IntakeUntilLimitCmd());
	AddParallel(new DelayedElevatorToHeightGrp(0.5,0.0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000,1600}, std::vector<double>{80, 45}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double>{400}, std::vector<double>{0}));

	AddSequential(new ReverseIntakeCmd(0.4));

}
