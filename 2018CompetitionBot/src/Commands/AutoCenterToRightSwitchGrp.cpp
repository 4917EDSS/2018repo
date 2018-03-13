#include <Commands/AutoCenterToRightSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"

AutoCenterToRightSwitchGrp::AutoCenterToRightSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));


	AddSequential(new SilkyMotionCmd(std::vector<double> {1300, 1400}, std::vector<double> {25, 0}));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-900, -950}, std::vector<double> {10, -25}));

	AddParallel(new IntakeUntilLimitCmd());


	AddSequential(new SilkyMotionCmd(std::vector<double> {950, -900}, std::vector<double> {-15,20}));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {1000, 1000}, std::vector<double> {10, -10}));

	AddSequential(new ReverseIntakeCmd(0.50));


//box 3

		AddParallel(new ZeroElevatorCmd());

		AddSequential(new SilkyMotionCmd(std::vector<double> {-850, -900}, std::vector<double> {10, -25}));

		AddParallel(new IntakeUntilLimitCmd());


		AddSequential(new SilkyMotionCmd(std::vector<double> {900, -900}, std::vector<double> {-15,20}));

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

		AddSequential(new ReverseIntakeCmd(0.50));

	// Deliver box


}
