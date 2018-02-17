#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "AutoScaleRightGrp.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"

AutoScaleRightGrp::AutoScaleRightGrp() {

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(20));

	AddSequential(new DriveStraightCmd(7500,0.0));

	AddSequential(new MoveElevatorToHeightCmd(500));

	AddSequential(new DriveTurnCmd(-90));

	AddSequential(new ReverseIntakeCmd(1));

}
