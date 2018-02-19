#include <Commands/AutoSwitchLeftToRightBackGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"

AutoSwitchLeftToRightBackGrp::AutoSwitchLeftToRightBackGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	AddSequential(new ZeroElevatorCmd());

	AddSequential(new DriveStraightCmd(5500,0.0));

	AddSequential(new DriveTurnCmd(90));

	AddSequential(new DriveStraightCmd(3700,90));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveTurnCmd(180));

	AddSequential(new DriveStraightCmd(650,180));

	AddSequential(new ReverseIntakeCmd(1));
}

	//Then go forward until it hits the switch



	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

