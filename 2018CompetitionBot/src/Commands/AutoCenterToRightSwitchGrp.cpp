#include <Commands/AutoCenterToRightSwitchGrp.h>
#include "DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/TimedFoldArmsDownCmd.h"
#include "Subsystems/IntakeSub.h"

AutoCenterToRightSwitchGrp::AutoCenterToRightSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	float heading = 0;
	AddParallel (new TimedFoldArmsDownCmd(IntakeSub::TIME_TO_LOWER_ARMS));
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	heading = 20;
	AddSequential(new DriveTurnCmd(heading)); // Need to just turn one side, other side wont be able to go back since on wall

	AddSequential(new DriveStraightCmd(2700,heading));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new DriveStraightCmd(-1500,heading));

	heading = -25;
	AddSequential(new DriveTurnCmd(heading));

	AddParallel(new IntakeUntilLimitCmd());

	AddSequential(new DriveStraightCmd(600,heading));

	AddSequential(new DriveStraightCmd(-600,heading));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	heading = 15;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(1400,heading));

	AddSequential(new ReverseIntakeCmd(0.50));


	// Deliver box


}
