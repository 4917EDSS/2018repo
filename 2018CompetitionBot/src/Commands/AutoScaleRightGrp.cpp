#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "AutoScaleRightGrp.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"

AutoScaleRightGrp::AutoScaleRightGrp() {

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(20));

	AddSequential(new DriveStraightCmd(6500,0.0));

	AddParallel(new MoveElevatorToHeightCmd(500));

	AddSequential(new DriveTurnCmd(-45));

	AddSequential(new DriveStraightCmd(500,-45));

	AddSequential(new ReverseIntakeCmd(1));

}
