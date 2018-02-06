#include "SilkyMotionCmd.h"

SilkyMotionCmd::SilkyMotionCmd(std::vector<double> dis, std::vector<double> ang) : smm(dis, ang,
		 MAX_LIN_ACCEL, MAX_LIN_DECEL, MAX_LIN_VEL,
		 MAX_ANG_ACCEL, MAX_ANG_DECEL, MAX_ANG_VEL,
		 STOPPING_DISTANCE_TOLERANCE, STOPPING_SPEED_TOLERANCE, STOPPING_ANGLE_TOLERANCE) {
	Requires(drivetrainSub.get());
}

// Called just before this Command runs the first time
void SilkyMotionCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SilkyMotionCmd::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SilkyMotionCmd::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SilkyMotionCmd::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SilkyMotionCmd::Interrupted() {

}
