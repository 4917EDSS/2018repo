#include "AutoSwitchRightGrp.h"
#include "DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"

AutoSwitchRightGrp::AutoSwitchRightGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddParallel(new MoveElevatorToHeightCmd(205));

	AddSequential(new DriveTurnCmd(20)); // Need to just turn one side, other side wont be able to go back since on wall

	AddSequential(new DriveStraightCmd(3000,20));

	AddSequential(new ReverseIntakeCmd(2));


	// Deliver box


}
