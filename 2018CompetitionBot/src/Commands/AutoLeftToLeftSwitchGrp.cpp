#include "AutoLeftToLeftSwitchGrp.h"
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
AutoLeftToLeftSwitchGrp::AutoLeftToLeftSwitchGrp() {

	AddSequential(new DriveStraightCmd(3798,0.0));
	AddSequential(new DriveTurnCmd(90));
	AddSequential(new DriveStraightCmd(202,90.0));
	//Drop Box
}
