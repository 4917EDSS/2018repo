#include <Commands/AutoRightToLeftScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/RightToLeftScaleGrp.h"

AutoRightToLeftScaleGrp::AutoRightToLeftScaleGrp() {
	AddSequential(new RightToLeftScaleGrp());

	AddParallel(new IntakeUntilLimitCmd());
	AddParallel(new DelayedElevatorToHeightGrp(0.5,0.0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-800,2700}, std::vector<double>{35, 75}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::AUTO_FIRST_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-2700, 800}, std::vector<double>{-75, -35}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-700}, std::vector<double>{0}));


}
