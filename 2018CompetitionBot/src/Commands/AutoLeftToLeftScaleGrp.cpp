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

	AddParallel(new DelayedElevatorToHeightGrp(ElevatorSub::CARRY_HEIGHT,4.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {4210, 2300, 3340, 1300}, std::vector<double> {0, 90, 0, -120}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new IntakeUntilLimitCmd());

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0.0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000,1600}, std::vector<double>{-80, -45}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1600, 1000}, std::vector<double>{45, 70}));

	AddSequential(new ReverseIntakeCmd(0.1));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-700}, std::vector<double>{0}));



}
