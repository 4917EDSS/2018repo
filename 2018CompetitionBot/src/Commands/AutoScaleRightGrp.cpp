#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "AutoScaleRightGrp.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"

AutoScaleRightGrp::AutoScaleRightGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddParallel(new MoveElevatorToHeightCmd(20));

	AddSequential(new DriveStraightCmd(7500,0.0));

	AddParallel(new MoveElevatorToHeightCmd(500));

	AddSequential(new DriveTurnCmd(-90));

	AddSequential(new DriveStraightCmd(200,-90.0));

	AddSequential(new ReverseIntakeCmd(1));

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
