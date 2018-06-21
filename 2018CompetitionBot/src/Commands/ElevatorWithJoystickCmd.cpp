#include "ElevatorWithJoystickCmd.h"

ElevatorWithJoystickCmd::ElevatorWithJoystickCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevatorSub.get());
}

// Called just before this Command runs the first time
void ElevatorWithJoystickCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorWithJoystickCmd::Execute() {

	std::shared_ptr<frc::Joystick> operatorJoystick = oi->getOperatorController();

	double verticalStick = operatorJoystick->GetRawAxis(OPERATOR_ELEVATOR_AXIS);
	verticalStick = pow(verticalStick, 3);

	// Demo mode slows down the elevator for inexperienced users
	if (CommandBase::isDemoMode) {
		verticalStick /= 2;
	}

	if (elevatorSub->isElevatorDown()){
		elevatorSub->setElevatorMotor(-verticalStick);
	} else {
		if (verticalStick > -0.01 && verticalStick < 0.01){
			elevatorSub->setElevatorMotor(0.04001);
		} else {
			elevatorSub->setElevatorMotor((-verticalStick) + 0.04);
		}
	}
}



// Make this return true when this Command no longer needs to run execute()
bool ElevatorWithJoystickCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorWithJoystickCmd::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorWithJoystickCmd::Interrupted() {

}
