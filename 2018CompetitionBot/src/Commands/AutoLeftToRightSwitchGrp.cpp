#include "AutoLeftToRightSwitchGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"

AutoLeftToRightSwitchGrp::AutoLeftToRightSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	AddSequential(new DriveStraightCmd(6223));

	AddSequential(new DriveTurnCmd(90));

	AddSequential(new DriveStraightCmd(4385));

	AddSequential(new DriveTurnCmd(90));

	AddSequential(new DriveStraightCmd(2679));

	AddSequential(new DriveTurnCmd(90));

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
