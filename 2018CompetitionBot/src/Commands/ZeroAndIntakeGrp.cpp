#include "ZeroAndIntakeGrp.h"
#include "ZeroElevatorCmd.h"
#include "IntakeUntilLimitCmd.h"

ZeroAndIntakeGrp::ZeroAndIntakeGrp() {
	AddSequential(new ZeroElevatorCmd());
	AddSequential(new IntakeUntilLimitCmd());

}
