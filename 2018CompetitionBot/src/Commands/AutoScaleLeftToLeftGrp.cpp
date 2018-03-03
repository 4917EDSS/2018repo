#include <Commands/AutoScaleLeftToLeftGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"

AutoScaleLeftToLeftGrp::AutoScaleLeftToLeftGrp() {
	float heading = 0;

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT));

	AddSequential(new DriveStraightCmd(6500,heading));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	heading = 45;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(500,heading));

	AddSequential(new ReverseIntakeCmd(1));
}
