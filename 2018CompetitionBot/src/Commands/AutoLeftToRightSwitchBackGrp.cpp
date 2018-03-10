#include <Commands/AutoLeftToRightSwitchBackGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/TimedFoldArmsDownCmd.h"
#include "Subsystems/IntakeSub.h"

AutoLeftToRightSwitchBackGrp::AutoLeftToRightSwitchBackGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	float heading = 0;

	AddParallel (new TimedFoldArmsDownCmd(IntakeSub::TIME_TO_LOWER_ARMS));
	AddSequential(new ZeroElevatorCmd());

	AddSequential(new DriveStraightCmd(5500,heading));

	heading = 90;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(3700,heading));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	heading = 180;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(650,heading));

	AddSequential(new ReverseIntakeCmd(1));
}

	//Then go forward until it hits the switch



	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

