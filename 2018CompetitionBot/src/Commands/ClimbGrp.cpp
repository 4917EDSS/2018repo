/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/FoldArmsUpCmd.h>
#include "ClimbGrp.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ExtendClimbBarCmd.h"


ClimbGrp::ClimbGrp() {

	AddSequential(new ExtendClimbBarCmd());

	AddSequential(new WaitCommand(1));



}
