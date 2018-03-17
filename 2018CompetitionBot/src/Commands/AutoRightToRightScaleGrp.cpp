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
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"

AutoRightToRightScaleGrp::AutoRightToRightScaleGrp() {

	AddParallel (new FoldArmsDownCmd());
	AddSequential(new ZeroElevatorCmd());

	AddSequential(new MoveElevatorToHeightCmd(ElevatorSub::CARRY_HEIGHT));

	AddParallel(new DelayedElevatorToHeightGrp(0.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {6000,1000}, std::vector<double> {0, -45}));

	AddSequential(new ReverseIntakeCmd(1));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-500}, std::vector<double> {-45}));

	AddSequential(new ZeroElevatorCmd());



}
