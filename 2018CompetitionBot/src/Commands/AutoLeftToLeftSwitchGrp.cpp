#include "AutoLeftToLeftSwitchGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
AutoLeftToLeftSwitchGrp::AutoLeftToLeftSwitchGrp() {

	AddSequential(new DriveStraightCmd(3798));
	AddSequential(new DriveTurnCmd(90));
	AddSequential(new DriveStraightCmd(202));
	//Drop Box
}
