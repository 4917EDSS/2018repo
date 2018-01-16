#include "AutoSwitchRightGrp.h"
#include "DriveStraightCmd.h"
#include "DriveTurnCmd.h"
AutoSwitchRightGrp::AutoSwitchRightGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	AddSequential(new DriveTurnCmd(30)); // Need to just turn one side, other side wont be able to go back since on wall

	AddSequential(new DriveStraightCmd(3766));


	// Deliver box


}
