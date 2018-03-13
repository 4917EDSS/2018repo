#include <Commands/AutoRightToRightScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "MoveElevatorToHeightCmd.h"
#include "ReverseIntakeCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Commands/DriveVisionBoxCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"

AutoRightToRightScaleGrp::AutoRightToRightScaleGrp() {

	float heading = 0;

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddParallel(new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {6500,0}, std::vector<double> {0, -45}));

	AddParallel(new DriveTurnCmd(-45));

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new DriveStraightCmd(500,-45));

	AddSequential(new ReverseIntakeCmd(1));

	AddParallel(new SilkyMotionCmd(std::vector<double> {-500}, std::vector<double> {-45}));

	AddSequential(new ZeroElevatorCmd());

	heading = -160;
	AddSequential(new DriveTurnCmd(-160));

	AddSequential(new DriveVisionBoxCmd());

}
