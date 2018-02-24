#include <Commands/AutoSwitchCenterToLeftGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"

AutoSwitchCenterToLeftGrp::AutoSwitchCenterToLeftGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveTurnCmd(-24));

	AddSequential(new DriveStraightCmd(3000,-24));

	AddSequential(new ReverseIntakeCmd(2));

	AddSequential(new DriveStraightCmd(-1500,-24));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new DriveTurnCmd(24));

	AddParallel(new IntakeUntilLimitCmd());

	AddSequential(new DriveStraightCmd(1000,0));

	AddSequential(new DriveStraightCmd(-1000,0));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveTurnCmd(-24));

	AddSequential(new DriveStraightCmd(1500,-24));

	AddSequential(new ReverseIntakeCmd(2));

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
