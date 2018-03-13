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

AutoRightToLeftScaleGrp::AutoRightToLeftScaleGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


	AddParallel (new FoldArmsDownCmd());

	AddParallel(new DelayedElevatorToHeightGrp(5.0,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddParallel(new DelayedElevatorToHeightGrp(4.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {4380, 2000, 3400, 1300}, std::vector<double> {0, -90, 0, 120}));

	AddParallel(new IntakeUntilLimitCmd());

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1200, 1700}, std::vector<double> {90, 90}));

	AddParallel(new IntakeUntilLimitCmd());

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000,1500}, std::vector<double>{80, 50}));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1500, 1000}, std::vector<double>{-50, -80}));

	AddSequential(new ReverseIntakeCmd(0.45));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-700}, std::vector<double>{0}));





}
