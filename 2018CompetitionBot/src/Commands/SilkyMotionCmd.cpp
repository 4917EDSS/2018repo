#include "SilkyMotionCmd.h"
#include "iostream"

SilkyMotionCmd::SilkyMotionCmd(std::vector<double> dis, std::vector<double> ang) : smm(dis, ang,
		 MAX_LIN_ACCEL, MAX_LIN_DECEL, MAX_LIN_VEL, MAX_ANG_ACCEL) {
	Requires(drivetrainSub.get());
}

// Called just before this Command runs the first time
void SilkyMotionCmd::Initialize() {
}


// Called repeatedly when this Command is scheduled to run
void SilkyMotionCmd::Execute() {
	PathInfo p = smm.getCurrentPathInfo(TimeSinceInitialized());
	logger.send(logger.DEBUG, "%f, %f, %f, %f, %f, %f", p.ang, p.dis, p.lin_vel, p.lin_accel, p.ang_vel, TimeSinceInitialized());
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
