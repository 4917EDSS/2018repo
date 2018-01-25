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

	if (leftStick < 0.01 && leftStick > -0.01) {
		if (wasDrivingStraight > 0) {
			drivetrainSub->disableBalancerPID();
			wasDrivingStraight = 0;
			std::cout << "In Disable PID one" << std::endl;;
		}

		drivetrainSub->drive(rightStick, -rightStick);
	} else if (rightStick < 0.01 && rightStick > -0.01) {
		if (wasDrivingStraight == 0) {
			timeSinceDrivingStraight = RobotController::GetFPGATime();
			wasDrivingStraight = 1;
			std::cout << "In Enable PID" << std::endl;
		}
		if (((RobotController::GetFPGATime() - timeSinceDrivingStraight) >= AHRS_DELAY_TIME) && wasDrivingStraight == 1) {
			drivetrainSub->resetAHRS();
			drivetrainSub->enableBalancerPID(0);
			wasDrivingStraight = 2;
		}
		drivetrainSub->driverDriveStraight(-leftStick);
	} else {
		if (wasDrivingStraight > 0) {
			drivetrainSub->disableBalancerPID();
			wasDrivingStraight = 0;
			std::cout << "In Disable PID two" << std::endl;
		}
		if (leftStick < 0) {
			if (rightStick < 0) {
				drivetrainSub->drive(-leftStick + fabs(rightStick) * leftStick / 1.5, -leftStick);

			} else {
				drivetrainSub->drive(-leftStick, -leftStick + fabs(rightStick) * leftStick / 1.5);

			}
		}
		else {
			if (rightStick > 0) {
				drivetrainSub->drive(-leftStick + fabs(rightStick) * leftStick / 1.5, -leftStick);

			} else {
				drivetrainSub->drive(-leftStick, -leftStick + fabs(rightStick) * leftStick / 1.5);

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
