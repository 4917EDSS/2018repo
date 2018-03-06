#include <Commands/AutoScaleRightToRightGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/DriveVisionBoxCmd.h"
#include "Subsystems/ElevatorSub.h"

AutoScaleRightToRightGrp::AutoScaleRightToRightGrp() {

	float heading = 0;
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(200));

	AddSequential(new DriveStraightCmd(6500,heading));

	heading = -45;
	AddParallel(new DriveTurnCmd(heading));

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_MEDIUM_HEIGHT));

	AddSequential(new DriveStraightCmd(500,heading));

	AddSequential(new ReverseIntakeCmd(1));

	AddParallel(new DriveStraightCmd(-500,heading));

	AddSequential(new ZeroElevatorCmd());

	heading = -160
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveVisionBoxCmd());

}
