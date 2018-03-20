#include <Commands/AutoRightToRightSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/SilkyMotionCmd.h"
#include "Subsystems/IntakeSub.h"

AutoRightToRightSwitchGrp::AutoRightToRightSwitchGrp() {
//	If you start from the right corner:
		AddParallel (new FoldArmsDownCmd());
		AddSequential(new ZeroElevatorCmd());

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1300}, std::vector<double> {-35, 10}));

		AddSequential(new ReverseIntakeCmd(0.5));

		AddParallel(new ZeroElevatorCmd());
		AddParallel(new IntakeUntilLimitCmd());
		AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 2500}, std::vector<double> {0, -45}));

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {-2500, 2000}, std::vector<double> {50, 0}));

		AddSequential(new ReverseIntakeCmd(0.5));

		AddParallel(new ZeroElevatorCmd());
		AddParallel(new IntakeUntilLimitCmd());
		AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 2500}, std::vector<double> {0, -45}));

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {-1000}, std::vector<double> {50}));

}
