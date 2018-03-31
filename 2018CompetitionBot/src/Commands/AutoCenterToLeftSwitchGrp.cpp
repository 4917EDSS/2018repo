#include <Commands/AutoCenterToLeftSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"

AutoCenterToLeftSwitchGrp::AutoCenterToLeftSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1300}, std::vector<double> {-35, 10}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1630}, std::vector<double> {-10}));  //Took second box
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double>{600}, std::vector<double>{53}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-600, 1600}, std::vector<double> {-53, 5}));	//!

	AddSequential(new ReverseIntakeCmd(0.4));     //Dropped second box

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1150}, std::vector<double> {0}));
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {550, -700}, std::vector<double> {40, -25}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1100, 400}, std::vector<double> {-25, 10}));

	AddSequential(new ReverseIntakeCmd(0.50));

}
