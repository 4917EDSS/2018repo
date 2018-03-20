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
	AddSequential(new SilkyMotionCmd(std::vector<double> {1300, 1500}, std::vector<double> {25, 0}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new ZeroElevatorCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-900, -950}, std::vector<double> {10, -30}));

	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {950, -900}, std::vector<double> {-35,30}));		//Took second box, reversing

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1000, 900}, std::vector<double> {35, -10}));		//Drop second box

	AddSequential(new ReverseIntakeCmd(0.4));

	//box 3:
	AddParallel(new ZeroElevatorCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-850, -900}, std::vector<double> {10, -25}));

	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {900, -1200}, std::vector<double> {-25,10}));	//took box 3, reversing

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1700}, std::vector<double> {50}));

	AddSequential(new ReverseIntakeCmd(0.50)); // Deliver box
}
