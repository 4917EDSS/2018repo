/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoLeftToLeftScaleToLeftSwitchGrp.h"
#include <Commands/AutoLeftToLeftScaleGrp.h>
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
#include "Commands/LeftToLeftScaleGrp.h"

AutoLeftToLeftScaleToLeftSwitchGrp::AutoLeftToLeftScaleToLeftSwitchGrp() {
	AddSequential(new LeftToLeftScaleGrp());

	AddParallel(new DelayedElevatorToHeightGrp(0.5, 0));
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-500, 1950}, std::vector<double> {45, 90}));

	AddParallel(new SilkyMotionCmd(std::vector<double> {200}, std::vector<double> {0}));
	AddSequential(new DelayedElevatorToHeightGrp(0,ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new ReverseIntakeCmd(0.4));
}
