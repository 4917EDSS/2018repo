/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/FoldArmsDownCmd.h>
#include "AutoRightToRightSwitchToLeftScaleGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"
#include "Subsystems/ElevatorSub.h"

AutoRightToRightSwitchToLeftScaleGrp::AutoRightToRightSwitchToLeftScaleGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	AddParallel (new FoldArmsDownCmd());
	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {3000,1050}, std::vector<double> {0,-90}));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-2000,300}, std::vector<double> {-135,45}));
	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {1300,500}, std::vector<double> {40,35}));

	AddParallel(new DelayedElevatorToHeightGrp(2,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-700,3500, 1000}, std::vector<double> {-90,0,180}));
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
