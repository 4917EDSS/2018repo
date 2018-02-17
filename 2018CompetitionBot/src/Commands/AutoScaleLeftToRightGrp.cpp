#include "AutoScaleLeftToRightGrp.h"
#include <Commands/DriveStraightCmd.h>
#include <Commands/DriveTurnCmd.h>
#include "Commands/ZeroElevatorCmd.h"

AutoScaleLeftToRightGrp::AutoScaleLeftToRightGrp() {
	AddSequential(new ZeroElevatorCmd());
	AddSequential(new DriveStraightCmd(6803,0.0));
	AddSequential(new DriveTurnCmd(90));
	AddSequential(new DriveStraightCmd(5799,90));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(2395,0.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(1075,-90));
}
