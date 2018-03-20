/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoLeftToRightScaleToRightSwitchGrp.h"
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/LeftToRightScaleGrp.h"

AutoLeftToRightScaleToRightSwitchGrp::AutoLeftToRightScaleToRightSwitchGrp() {
	AddSequential(new LeftToRightScaleGrp());

	AddParallel(new IntakeUntilLimitCmd());
	AddParallel(new DelayedElevatorToHeightGrp(0.5,0.0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000,1600}, std::vector<double>{-80, -45}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double>{400}, std::vector<double>{0}));

	AddSequential(new ReverseIntakeCmd(0.4));
}
