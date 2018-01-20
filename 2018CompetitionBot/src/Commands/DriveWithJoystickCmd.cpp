#include "DriveWithJoystickCmd.h"
#include "OI.h"
#include <iostream>

DriveWithJoystickCmd::DriveWithJoystickCmd() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(drivetrainSub.get());
}

// Called just before this Command runs the first time
void DriveWithJoystickCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystickCmd::Execute() {
	std::shared_ptr<frc::Joystick> driverJoystick = oi->getDriverController();

	double rightStick = driverJoystick->GetZ();
	double leftStick = driverJoystick->GetY();
	rightStick = pow(rightStick, 3);
	leftStick = pow(leftStick, 3);

	std::cout << "Left Stick : " << leftStick << std::endl;
	std::cout << "Right Stick : " << rightStick << std::endl;
	if (leftStick < 0.1 && leftStick > -0.1) {
		drivetrainSub->drive(rightStick, -rightStick);

	} else {
		if (leftStick < 0) {
			if (rightStick < 0) {
				drivetrainSub->drive(-leftStick + fabs(rightStick) * leftStick / 2.0, -leftStick);
				std::cout << "Left Drive : " << -leftStick + fabs(rightStick) * leftStick / 2.0 << std::endl;
				std::cout << "Right Drive : " << -leftStick << std::endl;
			} else {
				drivetrainSub->drive(-leftStick, -leftStick + fabs(rightStick) * leftStick / 2.0);
				std::cout << "Left Drive : " << -leftStick << std::endl;
				std::cout << "Right Drive : " << -leftStick + fabs(rightStick) * leftStick / 2.0 << std::endl;
			}
		}
		else {
			if (rightStick > 0) {
				drivetrainSub->drive(-leftStick + fabs(rightStick) * leftStick / 2.0, -leftStick);
				std::cout << "Left Drive : " << -leftStick + fabs(rightStick) * leftStick / 2.0 << std::endl;
				std::cout << "Right Drive : " << -leftStick << std::endl;
			} else {
				drivetrainSub->drive(-leftStick, -leftStick + fabs(rightStick) * leftStick / 2.0);
				std::cout << "Left Drive : " << -leftStick << std::endl;
				std::cout << "Right Drive : " << -leftStick + fabs(rightStick) * leftStick / 2.0 << std::endl;
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystickCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystickCmd::End() {
	drivetrainSub->drive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystickCmd::Interrupted() {

}
