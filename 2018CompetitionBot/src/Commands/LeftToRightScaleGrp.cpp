/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LeftToRightScaleGrp.h"
#include <Commands/AutoRightToRightScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/DriveVisionBoxCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"

LeftToRightScaleGrp::LeftToRightScaleGrp() {

	AddParallel (new FoldArmsDownCmd());
	AddParallel(new DelayedElevatorToHeightGrp(ElevatorSub::CARRY_HEIGHT,5.75,ElevatorSub::AUTO_FIRST_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {4210, 2300, 3340, 1300}, std::vector<double> {0, 90, 0, -110}));

	AddSequential(new ReverseIntakeCmd(0.4));
}
