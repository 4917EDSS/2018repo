#include <Commands/AutoRightToLeftSwitchGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/SilkyMotionCmd.h"
#include "Subsystems/IntakeSub.h"

AutoRightToLeftSwitchGrp::AutoRightToLeftSwitchGrp() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


//	float heading = 0;

		AddParallel (new FoldArmsDownCmd());
		AddSequential(new ZeroElevatorCmd());

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 3000, 1300}, std::vector<double> {-90, 0, 90}));
		AddSequential(new ReverseIntakeCmd(0.5));

		AddParallel(new ZeroElevatorCmd());
		AddParallel(new IntakeUntilLimitCmd());
		AddSequential(new SilkyMotionCmd(std::vector<double> {-2000, 1100}, std::vector<double> {0, 45}));

		AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
		AddSequential(new SilkyMotionCmd(std::vector<double> {-1100, 2000}, std::vector<double> {-45, 0}));
		AddSequential(new ReverseIntakeCmd(0.5));

	}

	//Then go forward until it hits the switch



	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

