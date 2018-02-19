#include <Commands/AutoScaleRightToRightGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/DriveVisionBoxCmd.h"
#include "Subsystems/ElevatorSub.h"

AutoScaleRightToRightGrp::AutoScaleRightToRightGrp() {

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(200));

	AddSequential(new DriveStraightCmd(6500,0.0));

	AddParallel(new DriveTurnCmd(-45));

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_MEDIUM_HEIGHT));

	AddSequential(new DriveStraightCmd(500,-45));

	AddSequential(new ReverseIntakeCmd(1));

	AddParallel(new DriveStraightCmd(-500,-45));

	AddSequential(new ZeroElevatorCmd());

	AddSequential(new DriveTurnCmd(-160));

	AddSequential(new DriveVisionBoxCmd());

}
