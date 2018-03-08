#include <Commands/AutoLeftToRightScaleGrp.h>
#include <Commands/DriveStraightCmd.h>
#include <Commands/DriveTurnCmd.h>
#include "Commands/ZeroElevatorCmd.h"

AutoLeftToRightScaleGrp::AutoLeftToRightScaleGrp() {

	float heading = 0;

	AddSequential(new ZeroElevatorCmd());

	AddSequential(new DriveStraightCmd(6803,heading));

	heading = 90;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(5799,heading));

	heading = -90;
	AddSequential(new DriveTurnCmd(heading));

	heading = 0;
	AddSequential(new DriveStraightCmd(2395,heading));

	heading = -90;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(1075,heading));
}
