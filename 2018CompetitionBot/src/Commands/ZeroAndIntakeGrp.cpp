#include "ZeroAndIntakeGrp.h"
#include "ZeroElevatorCmd.h"
#include "IntakeUntilLimitCmd.h"
#include "MoveElevatorToHeightCmd.h"

ZeroAndIntakeGrp::ZeroAndIntakeGrp() {
	AddSequential(new ZeroElevatorCmd());
	AddSequential(new IntakeUntilLimitCmd());
	AddSequential(new MoveElevatorToHeightCmd(60));
	// TODO: add raise height
}
