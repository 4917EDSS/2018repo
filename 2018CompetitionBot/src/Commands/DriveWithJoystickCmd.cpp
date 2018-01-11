#include "DriveWithJoystickCmd.h"
#include "OI.h"

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

  double rightStick = driverJoystick->GetRawAxis(DRIVER_RIGHT_TANK_DRIVER_AXIS);
  double leftStick = driverJoystick->GetRawAxis(DRIVER_LEFT_FPS_DRIVER_AXIS);
  if (leftStick < 0.1 && leftStick > -0.1) {
    Drive(rightStick, -rightStick);
  } else {
    if (rightStick < 0) {
      drivetrainSub->drive(leftstick - rightStick * leftStick / 2, leftStick);
    } else {
      drivetrainSub->drive(leftStick, leftStick - rightstick * leftStick / 2);
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
