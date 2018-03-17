#include <Commands/AutoRightToRightScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/DriveVisionBoxCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"

AutoRightToRightScaleGrp::AutoRightToRightScaleGrp() {

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT));

	AddParallel(new DelayedElevatorToHeightGrp(ElevatorSub::CARRY_HEIGHT, 0.15,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {5200, 1500}, std::vector<double> {0, -45}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-500, 1500}, std::vector<double> {-45, -90}));


	AddParallel(new DelayedElevatorToHeightGrp(0, 0.5,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1500, 500}, std::vector<double> {90, 45}));

	AddSequential(new ReverseIntakeCmd(0.4));

}
