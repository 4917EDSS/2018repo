/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoRightToRightScaleToRightSwitchGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"


AutoRightToRightScaleToRightSwitch::AutoRightToRightScaleToRightSwitch() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


	float heading = 0;

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_MEDIUM_HEIGHT));
	AddSequential(new DriveStraightCmd(6000, heading));

	heading=-20;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new ReverseIntakeCmd(0.5));

	heading=-160;
	AddParallel((new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT)));
	AddSequential(new DriveTurnCmd(heading));

	AddParallel(new DriveStraightCmd(2000,heading));
	AddSequential(new IntakeUntilLimitCmd());

	AddParallel(new DriveStraightCmd(-100,heading));
	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new ReverseIntakeCmd(0.5));


	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
