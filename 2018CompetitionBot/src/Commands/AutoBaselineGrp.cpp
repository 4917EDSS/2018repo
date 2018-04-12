/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoBaselineGrp.h"
#include "SilkyMotionCmd.h"
#include "FoldArmsDownCmd.h"
#include "ZeroElevatorCmd.h"

AutoBaselineGrp::AutoBaselineGrp() {
	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {2900}, std::vector<double> {0}));


}
