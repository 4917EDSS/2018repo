#include <Commands/AutoRightToRightSwitchGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
AutoRightToRightSwitchGrp::AutoRightToRightSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


//	If you start from the right corner:

	float heading = 0;

		AddSequential(new ZeroElevatorCmd());

		heading = -15;
		AddSequential(new DriveTurnCmd(heading));

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

		AddSequential(new DriveStraightCmd(2500,heading));

		heading = 0;
		AddSequential(new DriveTurnCmd(0));

		AddSequential(new DriveStraightCmd(500,0));

		AddSequential(new ReverseIntakeCmd(1));



	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
