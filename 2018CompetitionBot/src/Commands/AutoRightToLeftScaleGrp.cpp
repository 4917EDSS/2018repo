#include <Commands/AutoRightToLeftScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"
#include "Commands/IntakeUntilLimitCmd.h"

AutoRightToLeftScaleGrp::AutoRightToLeftScaleGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


	AddParallel (new FoldArmsDownCmd());

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new DelayedElevatorToHeightGrp(4.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {4380, 2000, 3400, 1300}, std::vector<double> {0, -90, 0, 120}));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new IntakeUntilLimitCmd());

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));


	AddParallel(new DelayedElevatorToHeightGrp(0.5,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));


	AddSequential(new ReverseIntakeCmd(0.45));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-700}, std::vector<double>{0}));














}
