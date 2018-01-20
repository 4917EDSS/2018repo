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
	AddSequential(new DriveTurnCmd(120));
	AddSequential(new DriveTurnCmd(120));
	AddSequential(new DriveTurnCmd(120));
	AddSequential(new DriveStraightCmd(-1500));
	AddSequential(new DriveTurnCmd(-72.0));
	AddSequential(new DriveStraightCmd(2000));
	AddSequential(new DriveTurnCmd(-108));
	AddSequential(new DriveStraightCmd(1000));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(1732));
	AddSequential(new DriveStraightCmd(550));

}
