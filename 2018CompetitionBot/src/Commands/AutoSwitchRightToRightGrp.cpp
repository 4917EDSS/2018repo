#include <Commands/AutoSwitchRightToRightGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
AutoSwitchRightToRightGrp::AutoSwitchRightToRightGrp() {
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
	AddSequential(new DriveStraightCmd(2500,-45));

	heading = 0;
	AddSequential(new DriveTurnCmd(heading));
	AddSequential(new DriveStraightCmd(500,heading));
	AddSequential(new ReverseIntakeCmd(1));


	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
