#include <Commands/AutoSwitchLeftToLeftGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"


AutoSwitchLeftToLeftGrp::AutoSwitchLeftToLeftGrp() {

	float heading = 0;

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	heading = 25;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new DriveStraightCmd(2800,heading));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd);

	heading = 110;
	AddSequential(new DriveTurnCmd(heading));

	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new DriveStraightCmd(1800,heading));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveStraightCmd(-1700,heading));

	heading = 30;
	AddSequential(new DriveTurnCmd(heading));

	AddSequential(new ReverseIntakeCmd(0.5));

}
