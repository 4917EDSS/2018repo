#include <Commands/MoveElevatorToHeightCmd.h>
#include <iostream>


MoveElevatorToHeightCmd::MoveElevatorToHeightCmd(double height) : height(height) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void MoveElevatorToHeightCmd::Initialize() {
//	elevatorSub->enableLiftPID(elevatorSub->convertHeightToEncoder(height));
	elevatorSub->setTarget (height);
}

// Called repeatedly when this Command is scheduled to run
void MoveElevatorToHeightCmd::Execute() {
	if (height==0){
		elevatorSub->setElevatorMotor(-1.0);
	}else{
		elevatorSub->update();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveElevatorToHeightCmd::IsFinished() {
	if (TimeSinceInitialized() > 2.0){
		return true;
	}
	else{
		if (height==0){
			return elevatorSub->isElevatorDown();
		}else{
			return elevatorSub->isFinishedMove();
		}
	}
}

// Called once after isFinished returns true
void MoveElevatorToHeightCmd::End() {
//	elevatorSub->disableLiftPID();
	elevatorSub->setElevatorMotor(0.0);

	if (elevatorSub->isElevatorDown()){
		elevatorSub->setElevatorMotor(0.0);
	} else {
		elevatorSub->setElevatorMotor(0.04);
	}
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveElevatorToHeightCmd::Interrupted() {
	End();

	}
