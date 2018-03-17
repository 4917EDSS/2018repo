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

	AddParallel(new DelayedElevatorToHeightGrp(ElevatorSub::CARRY_HEIGHT, 0,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {2600, 2600, 1000}, std::vector<double> {-10, 10, -45}));

	//AddSequential(new SilkyMotionCmd(std::vector<double> {500}, std::vector<double> {-15}));


	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new ZeroElevatorCmd());
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-500, 1500}, std::vector<double> {-45, -90}));


	AddParallel(new DelayedElevatorToHeightGrp(0, 0,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-1500}, std::vector<double> {90}));

	AddParallel(new ReverseIntakeCmd(0.4));
	AddSequential(new SilkyMotionCmd(std::vector<double> {500}, std::vector<double> {45}));

}
