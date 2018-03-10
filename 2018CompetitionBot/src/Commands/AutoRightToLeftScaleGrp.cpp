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

AutoRightToLeftScaleGrp::AutoRightToLeftScaleGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


	AddParallel (new FoldArmsDownCmd());

	AddSequential(new ZeroElevatorCmd());

	AddParallel(new DelayedElevatorToHeightGrp(5,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {4380, 2000, 4000, 2200}, std::vector<double> {0, -90, 0, 150}));


	AddSequential(new ReverseIntakeCmd(0.5));


}
