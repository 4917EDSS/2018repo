#include "DriveVisionSwitchCmd.h"
#include <networktables/NetworkTableInstance.h>

DriveVisionSwitchCmd::DriveVisionSwitchCmd() {
	Requires(drivetrainSub.get());
}

void DriveVisionSwitchCmd::Initialize() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("pipeline").SetDouble(0.0);
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("ledMode").SetDouble(0.0);

}

void DriveVisionSwitchCmd::Execute() {
	float Kp = 0.01;  // Proportional control constant
	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	float tx = table->GetNumber("tx", 0.0);
	float steering_adjust = Kp*tx;
	drivetrainSub->drive(0.5+steering_adjust, 0.5-steering_adjust);

}


bool DriveVisionSwitchCmd::IsFinished() {

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
