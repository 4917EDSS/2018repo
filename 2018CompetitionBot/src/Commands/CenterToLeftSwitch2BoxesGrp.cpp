#include "CenterToLeftSwitch2BoxesGrp.h"
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"

CenterToLeftSwitch2BoxesGrp::CenterToLeftSwitch2BoxesGrp() {
	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1300}, std::vector<double> {-35, 10}));

	AddParallel(new ReverseIntakeCmd(0.4));
	AddSequential(new WaitCommand(0.1));


	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1630}, std::vector<double> {-10}));  //Took second box
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double>{600}, std::vector<double>{53})); //Might need a bit more to the right, intaking kicks robot a bit

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-600, 800, 900}, std::vector<double> {-53, 0, 10}));	//!

	AddParallel(new ReverseIntakeCmd(0.4));     //Dropped second box
	AddSequential(new WaitCommand(0.1));


	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-1250}, std::vector<double> {-5})); //backing to 3rd box
	AddParallel(new IntakeUntilLimitCmd());													// getting 3rd box
	AddSequential(new SilkyMotionCmd(std::vector<double> {550, -700}, std::vector<double> {40, -25}));
}
