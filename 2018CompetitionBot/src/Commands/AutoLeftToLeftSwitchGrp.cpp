#include <Commands/AutoLeftToLeftSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/SilkyMotionCmd.h"
#include "Subsystems/IntakeSub.h"

AutoLeftToLeftSwitchGrp::AutoLeftToLeftSwitchGrp() {

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());
	// first dropoff
	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {1600, 1400}, std::vector<double> {35, -10}));
	AddSequential(new ReverseIntakeCmd(0.5));
	// grab a second box
	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 2500}, std::vector<double> {0, 50}));
	// second dropoff
	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-2500, 2000}, std::vector<double> {-60, 0}));
	AddSequential(new ReverseIntakeCmd(0.5));
	// grab a third box
	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 2500}, std::vector<double> {0, 45}));
	// get ready for telly
	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1000}, std::vector<double> {-50}));

}
