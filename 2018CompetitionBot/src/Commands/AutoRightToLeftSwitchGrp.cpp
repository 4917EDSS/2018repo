#include "AutoRightToLeftSwitchGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"

AutoRightToLeftSwitchGrp::AutoRightToLeftSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

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

	AddSequential(new ZeroElevatorCmd());
	AddSequential(new DriveStraightCmd(5340,0.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(7032,-90.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(1400,-180.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(202,-270.0));

}
