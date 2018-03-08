#include <Commands/AutoRightToLeftScaleGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/TimedFoldArmsDownCmd.h"

AutoRightToLeftScaleGrp::AutoRightToLeftScaleGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	float heading = 0;

	AddParallel (new TimedFoldArmsDownCmd(TIME_TO_LOWER_ARMS));
	AddSequential(new ZeroElevatorCmd());

	AddSequential(new DriveStraightCmd(250,heading));

	heading = -90;
	AddSequential(new DriveTurnCmd(heading));

	/*AddSequential(new DriveStraightCmd(6171,0));
		AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(6147,-90));
		AddSequential(new DriveTurnCmd(90));
	AddSequential(new DriveStraightCmd(500,0));*/
	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
