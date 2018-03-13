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

	AddSequential(new SilkyMotionCmd(std::vector<double> {2750 }, std::vector<double> {15}));

	AddSequential(new SilkyMotionCmd(std::vector<double> {-900, -900 }, std::vector<double> {30,0}));


	AddSequential(new SilkyMotionCmd(std::vector<double> {950}, std::vector<double> {0}));

}
