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
#include "CenterToLeftSwitch2BoxesGrp.h"

AutoCenterToLeftSwitchToRightScaleGrp::AutoCenterToLeftSwitchToRightScaleGrp() {
	AddSequential (new CenterToLeftSwitch2BoxesGrp());

	AddSequential (new SilkyMotionCmd(std::vector<double> {700, 400, 3000}, std::vector<double> {95,0, -40}));
}
