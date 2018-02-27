#include <Commands/AutoSwitchLeftToLeftGrp.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"


AutoSwitchLeftToLeftGrp::AutoSwitchLeftToLeftGrp() {

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new DriveTurnCmd(25));

	AddSequential(new DriveStraightCmd(2800,25));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd);
	AddSequential(new DriveTurnCmd(110));

	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new DriveStraightCmd(1800,110));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new DriveStraightCmd(-1700,110));

	AddSequential(new DriveTurnCmd(30));

	AddSequential(new ReverseIntakeCmd(0.5));

}
