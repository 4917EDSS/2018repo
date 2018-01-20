#include "AutoScaleLeftToRightGrp.h"
#include <Commands/DriveStraightCmd.h>
#include <Commands/DriveTurnCmd.h>

AutoScaleLeftToRightGrp::AutoScaleLeftToRightGrp() {
	AddSequential(new DriveStraightCmd(3000,0.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000,-90.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000,-180.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000,90.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000,0.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(3000,-90.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveTurnCmd(120));
	AddSequential(new DriveTurnCmd(120));
	AddSequential(new DriveTurnCmd(120));
	AddSequential(new DriveStraightCmd(-1500,-180.0));
	AddSequential(new DriveTurnCmd(-72.0));
	AddSequential(new DriveStraightCmd(2000,102.0));
	AddSequential(new DriveTurnCmd(-108));
	AddSequential(new DriveStraightCmd(1000,-6.0));
	AddSequential(new DriveTurnCmd(-90));
	AddSequential(new DriveStraightCmd(1732,-96.0));
	AddSequential(new DriveStraightCmd(550,-96.0));

}
