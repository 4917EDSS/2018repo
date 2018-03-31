#include <Commands/AutoCenterToRightSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DelayedElevatorToHeightGrp.h"
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
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1400,-400}, std::vector<double> {10,-20}));

	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {850, -600}, std::vector<double> {-35,45}));		//Took second box, reversing

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {795, 875}, std::vector<double> {5, -20}));		//Drop second box

	AddSequential(new ReverseIntakeCmd(0.4));

	//box 3:
	AddParallel(new ZeroElevatorCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-850, -300}, std::vector<double> {5, -20}));

	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {700, -900}, std::vector<double> {-25,20}));	//took box 3, reversing

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1350}, std::vector<double> {28}));

	AddSequential(new ReverseIntakeCmd(0.50)); // Deliver box

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000}, std::vector<double>{0}));

}
