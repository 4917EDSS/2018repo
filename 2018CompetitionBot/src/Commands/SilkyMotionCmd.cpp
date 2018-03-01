#include "SilkyMotionCmd.h"
#include "iostream"

SilkyMotionCmd::SilkyMotionCmd(std::vector<double> dis, std::vector<double> ang) : smm(dis, ang,
		 MAX_LIN_ACCEL, MAX_LIN_DECEL, MAX_LIN_VEL, MAX_ANG_ACCEL) {
	Requires(drivetrainSub.get());
	prevTime = 0;
	prevError = 0;
}

// Called just before this Command runs the first time
void SilkyMotionCmd::Initialize() {
	drivetrainSub->resetAHRS();
	prevTime = 0;
	prevError = 0;
}


// Called repeatedly when this Command is scheduled to run
void SilkyMotionCmd::Execute() {
	double currTime = TimeSinceInitialized();
	PathInfo p = smm.getCurrentPathInfo(currTime);
	//logger.send(logger.DEBUG, "%f, %f, %f, %f, %f, %f", p.ang, p.dis, p.lin_vel, p.lin_accel, p.ang_vel, TimeSinceInitialized());

	double currDis=(drivetrainSub->getLeftEncoder()+drivetrainSub->getRightEncoder())/2;
	double currError=p.dis-currDis;
	double errorDer=(currError-prevError)/(currTime-prevTime);
	double angErr=p.ang-drivetrainSub->getAngle();
std::cout<< "current distance " << currDis<< " current error " << currError << " error derivative " << errorDer << " angle error " << angErr<< std::endl;
	drivetrainSub->drive(P_DIS*currError+D_DIS*errorDer+A_DIS*p.lin_accel+V_DIS*p.lin_vel+P_ANG*angErr+V_ANG*p.ang_vel,
			P_DIS*currError+D_DIS*errorDer+A_DIS*p.lin_accel+V_DIS*p.lin_vel-P_ANG*angErr-V_ANG*p.ang_vel);

	prevError = currError;
	prevTime = currTime;


}

// Make this return true when this Command no longer needs to run execute()
bool SilkyMotionCmd::IsFinished() {
	if (TimeSinceInitialized() > smm.getTotalTime()) {
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void SilkyMotionCmd::End() {
drivetrainSub->drive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SilkyMotionCmd::Interrupted() {
End();
}
