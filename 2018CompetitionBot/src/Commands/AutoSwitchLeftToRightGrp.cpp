#include <Commands/AutoSwitchLeftToRightGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"

AutoSwitchLeftToRightGrp::AutoSwitchLeftToRightGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

		AddSequential(new ZeroElevatorCmd());
		AddSequential(new DriveTurnCmd(30));
		AddSequential(new DriveStraightCmd(4500,30));
		AddSequential(new DriveTurnCmd(0));
		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new DriveStraightCmd(1000,0));
		AddSequential(new ReverseIntakeCmd(1));
	}

	//Then go forward until it hits the switch



	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

