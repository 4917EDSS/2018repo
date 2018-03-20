#include <Commands/AutoRightToLeftSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/SilkyMotionCmd.h"

AutoRightToLeftSwitchGrp::AutoRightToLeftSwitchGrp() {
//TODO: this auto does NOT dodge a third robot
	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 3000, 1300}, std::vector<double> {-90, 0, 90}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 1100}, std::vector<double> {0, 45}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1100, 2000}, std::vector<double> {-45, 0}));
	AddSequential(new ReverseIntakeCmd(0.5));
}

