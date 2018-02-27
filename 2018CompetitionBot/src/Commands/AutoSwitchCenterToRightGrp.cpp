#include <Commands/AutoSwitchCenterToRightGrp.h>
#include "DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"

AutoSwitchCenterToRightGrp::AutoSwitchCenterToRightGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveTurnCmd(20)); // Need to just turn one side, other side wont be able to go back since on wall

	AddSequential(new DriveStraightCmd(2700,20));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new DriveStraightCmd(-1500,20));

	AddSequential(new DriveTurnCmd(-25));

	AddParallel(new IntakeUntilLimitCmd());

	AddSequential(new DriveStraightCmd(600,-25));

	AddSequential(new DriveStraightCmd(-600,-25));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveTurnCmd(15));

	AddSequential(new DriveStraightCmd(1400,15));

	AddSequential(new ReverseIntakeCmd(0.50));


	// Deliver box


}
