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

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd());

	AddParallel(new IntakeUntilLimitCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 1100}, std::vector<double> {0, 45}));  //Took second box

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1100, 2000}, std::vector<double> {-45, 0}));	//!
	AddSequential(new ReverseIntakeCmd(0.5));                                                           //Dropped second box

	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1000, 500, -700}, std::vector<double> {0, 40, -20}));
	//AddSequential(new DriveStraightCmd(-400,heading));


	AddSequential(new SilkyMotionCmd(std::vector<double> {1100}, std::vector<double> {-20}));
	//AddSequential(new DriveStraightCmd(1400,heading));





	AddSequential(new SilkyMotionCmd(std::vector<double> {-900, 500}, std::vector<double> {-10, 45}));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-500, 900}, std::vector<double> {-45, 10}));
	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.
	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
