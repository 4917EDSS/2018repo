#include <Commands/AutoRightToRightScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/DriveVisionBoxCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Subsystems/IntakeSub.h"

AutoRightToRightScaleGrp::AutoRightToRightScaleGrp() {

	float heading = 0;

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT));

	AddSequential(new DriveStraightCmd(6500,heading));

	heading = -45;
	AddParallel(new DriveTurnCmd(heading));

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new DriveStraightCmd(500,heading));

	AddSequential(new ReverseIntakeCmd(1));

	AddParallel(new DriveStraightCmd(-500,heading));

	AddSequential(new ZeroElevatorCmd());

	heading = -160;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveVisionBoxCmd());

}
