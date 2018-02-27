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
	AddSequential(new ZeroElevatorCmd());
	AddSequential(new DriveTurnCmd(-15));
	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new DriveStraightCmd(2500,-45));
	AddSequential(new DriveTurnCmd(0));
	AddSequential(new DriveStraightCmd(500,0));
	AddSequential(new ReverseIntakeCmd(1));


	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
