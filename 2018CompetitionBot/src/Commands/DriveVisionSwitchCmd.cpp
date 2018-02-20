#include "DriveVisionSwitchCmd.h"
#include <networktables/NetworkTableInstance.h>

DriveVisionSwitchCmd::DriveVisionSwitchCmd(double distance) {
	targetDistance = distance;
	lastMoveTime=0;
	Requires(drivetrainSub.get());
}

void DriveVisionSwitchCmd::Initialize() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("pipeline").SetDouble(0.0);
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("ledMode").SetDouble(0.0);
	drivetrainSub->resetEncoders();


}

void DriveVisionSwitchCmd::Execute() {
	float Kp = 0.01;  // Proportional control constant
	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	float tx = table->GetNumber("tx", 0.0);
	float steering_adjust = Kp*tx;
	drivetrainSub->drive(0.5+steering_adjust, 0.5-steering_adjust);

}


bool DriveVisionSwitchCmd::IsFinished() {
	double timeFromLastMove = 0;
	double leftAndRightEncoderAvg = (fabs(drivetrainSub->getLeftEncoder()) + fabs(drivetrainSub->getRightEncoder()))/2;

	if(fabs(drivetrainSub->getLeftEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE && fabs(drivetrainSub->getRightEncoderSpeed()) < DISTANCE_SPEED_TOLERANCE){
		timeFromLastMove = TimeSinceInitialized() - lastMoveTime;
	} else {
		lastMoveTime = TimeSinceInitialized();
	}

	if((fabs(leftAndRightEncoderAvg) >= targetDistance) || (timeFromLastMove > 1)){
		return true;
	} //if enough distance, true
	else{
		return false;
	}

	return false;
}

// Called once after isFinished returns true
void DriveVisionSwitchCmd::End() {
	drivetrainSub->drive(0,0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveVisionSwitchCmd::Interrupted() {
	End();

}
