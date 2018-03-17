#include <Commands/AutoRightToLeftScaleGrp.h>
#include <Commands/FoldArmsDownCmd.h>
#include "Commands/DriveStraightCmd.h"
#include "Commands/DriveTurnCmd.h"
#include "Commands/ZeroElevatorCmd.h"
#include "Subsystems/IntakeSub.h"
#include "Commands/SilkyMotionCmd.h"
#include "Commands/MoveElevatorToHeightCmd.h"
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/DelayedElevatorToHeightGrp.h"
#include "Commands/IntakeUntilLimitCmd.h"

AutoRightToLeftScaleGrp::AutoRightToLeftScaleGrp() {

	AddParallel (new FoldArmsDownCmd());

	AddParallel(new DelayedElevatorToHeightGrp(4.75,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double> {4180, 2300, 3340, 1300}, std::vector<double> {0, -90, 0, 120}));

	AddSequential(new ReverseIntakeCmd(0.4));

	AddParallel(new IntakeUntilLimitCmd());

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1000,1450}, std::vector<double>{80, 45}));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,ElevatorSub::SCALE_BOX_HIGH_HEIGHT));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-1450, 1000}, std::vector<double>{-45, -80}));

	AddSequential(new ReverseIntakeCmd(0.4));

	//AddParallel(new DelayedElevatorToHeightGrp(0.5,0));

	AddSequential(new SilkyMotionCmd(std::vector<double>{-700}, std::vector<double>{0}));





}
