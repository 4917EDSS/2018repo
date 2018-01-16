#include "AutoLeftToLeftSwitchGrp.h"
#include "Commands/DriveStraightCmd.cpp"
#include "Commands/DriveTurnCmd.cpp"
AutoLeftToLeftSwitchGrp::AutoLeftToLeftSwitchGrp() {

	AddSequential(new DriveStraightCmd(3798));
	AddSequential(new DriveTurnCmd(90));
	AddSequential(new DriveStraightCmd(202));
	//Drop Box
}
