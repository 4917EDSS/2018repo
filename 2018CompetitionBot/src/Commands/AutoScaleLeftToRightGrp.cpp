#include "AutoScaleLeftToRightGrp.h"
#include <Commands/DriveStraightCmd.h>
#include <Commands/DriveTurnCmd.h>

AutoScaleLeftToRightGrp::AutoScaleLeftToRightGrp() {
	AddSequential(new DriveStraightCmd(3000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(-4000));
	AddSequential(new DriveTurnCmd(720));
}
