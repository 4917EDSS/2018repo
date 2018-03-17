#include <Commands/AutoLeftToLeftScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"

AutoLeftToLeftScaleGrp::AutoLeftToLeftScaleGrp() {

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT));

	AddParallel(new DelayedElevatorToHeightGrp(0.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {6000,1000}, std::vector<double> {0, -45}));

	AddSequential(new ReverseIntakeCmd(1));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-500}, std::vector<double> {-45}));

	AddSequential(new ZeroElevatorCmd());


}
