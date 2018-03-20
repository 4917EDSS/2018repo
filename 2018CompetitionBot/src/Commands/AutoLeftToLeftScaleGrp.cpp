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
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/LeftToLeftScaleGrp.h"

AutoLeftToLeftScaleGrp::AutoLeftToLeftScaleGrp() {
//TODO: We need to make the first box drop off a single silky
	AddSequential(new LeftToLeftScaleGrp());

	AddParallel(new DelayedElevatorToHeightGrp(0.5, 0));
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-500, 1950}, std::vector<double> {45, 90}));

	AddParallel(new SilkyMotionCmd(std::vector<double> {-1500}, std::vector<double> {-90}));
	AddSequential(new DelayedElevatorToHeightGrp(0,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {500}, std::vector<double> {-45}));

	AddSequential(new ReverseIntakeCmd(0.4));



}
