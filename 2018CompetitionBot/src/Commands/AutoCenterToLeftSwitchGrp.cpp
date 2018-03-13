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


	float heading = 0;
	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	heading = -30;
	AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1250}, std::vector<double> {heading, 0}));

	//AddSequential(new DriveStraightCmd(2750,heading));

	AddSequential(new ReverseIntakeCmd(0.5));

	AddParallel(new ZeroElevatorCmd());

	AddSequential(new SilkyMotionCmd(std::vector<double> {-850, -400}, std::vector<double> {0, 30}));
	//AddSequential(new DriveStraightCmd(-1250,heading));

	//AddSequential(new DriveTurnCmd(heading));   //Towards second box

	AddParallel(new IntakeUntilLimitCmd());

	AddSequential(new DriveStraightCmd(400,heading));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-300, -300}, std::vector<double> {45, -45}));
	//AddSequential(new DriveStraightCmd(-400,heading));

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));

	AddSequential(new DriveStraightCmd(1000,0));
	//AddSequential(new DriveStraightCmd(1400,heading));

	AddSequential(new ReverseIntakeCmd(0.5));
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
