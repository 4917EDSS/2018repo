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
#include "Commands/RightToRightScaleGrp.h"
//728 elevator top


AutoRightToRightScaleGrp::AutoRightToRightScaleGrp() {
	AddSequential(new RightToRightScaleGrp());

	AddParallel(new DelayedElevatorToHeightGrp(0.5, 0));
	AddParallel(new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double> {-500, 2300}, std::vector<double> {-45, -110}));


	AddParallel(new DelayedElevatorToHeightGrp(0,ElevatorSub::AUTO_FIRST_BOX_HEIGHT));
	AddSequential(new SilkyMotionCmd(std::vector<double> {-2300, 500}, std::vector<double> {110, 45}, 2000));

	AddParallel(new ReverseIntakeCmd(0.4));

	AddParallel(new DelayedElevatorToHeightGrp(0.5,0));
	AddSequential(new SilkyMotionCmd(std::vector<double>{-500}, std::vector<double>{-45}));
	AddParallel (new IntakeUntilLimitCmd());
	AddSequential(new SilkyMotionCmd(std::vector<double>{2100}, std::vector<double>{-70}));

}
