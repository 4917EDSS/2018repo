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
#include "CenterToRightSwitch2BoxesGrp.h"

AutoCenterToRightSwitchGrp::AutoCenterToRightSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddSequential (new CenterToRightSwitch2BoxesGrp());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1200}, std::vector<double> {28}));

	AddSequential(new ReverseIntakeCmd(0.50)); // Deliver box

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000}, std::vector<double>{0}));

}
