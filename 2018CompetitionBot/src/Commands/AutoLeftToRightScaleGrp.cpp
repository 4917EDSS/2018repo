#include <Commands/AutoLeftToRightScaleGrp.h>
#include <Commands/DriveStraightCmd.h>
#include <Commands/DriveTurnCmd.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/LeftToRightScaleGrp.h"

AutoLeftToRightScaleGrp::AutoLeftToRightScaleGrp() {
	AddSequential(new LeftToRightScaleGrp());

	AddParallel(new IntakeUntilLimitCmd());

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0.0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000,1450}, std::vector<double>{-70, -45}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1450, 1000}, std::vector<double>{45, 70}));

	AddSequential(new ReverseIntakeCmd(0.1));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-700}, std::vector<double>{0}));

}
