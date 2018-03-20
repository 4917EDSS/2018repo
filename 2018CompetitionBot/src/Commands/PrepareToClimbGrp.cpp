/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ElevatorSub.h"
#include "Commands/FoldArmsUpCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/PrepareToClimbGrp.h"
#include "Commands/ExtendClimbBarCmd.h"
#include "Commands/RetractClimbBarCmd.h"

PrepareToClimbGrp::PrepareToClimbGrp() {

	AddSequential(new FoldArmsUpCmd());

	AddSequential(new RetractClimbBarCmd());

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
}
