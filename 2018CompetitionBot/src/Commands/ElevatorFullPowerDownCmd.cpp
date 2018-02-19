#include "ElevatorFullPowerDownCmd.h"
ElevatorFullPowerDownCmd::ElevatorFullPowerDownCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());

}


// Called just before this Command runs the first time
void ElevatorFullPowerDownCmd::Initialize() {
elevatorSub->setElevatorMotorRaw(1.0);

}

// Called repeatedly when this Command is scheduled to run
void ElevatorFullPowerDownCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorFullPowerDownCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorFullPowerDownCmd::End() {
elevatorSub->setElevatorMotorRaw(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorFullPowerDownCmd::Interrupted() {
	End();
}
