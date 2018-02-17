#include <Commands/DriveWithDistanceCmd.h>
#include <networktables/NetworkTableInstance.h>


DriveToVisionCmd::DriveToVisionCmd(int distance) {
	this->targetDistance = distance;
}

// Called just before this Command runs the first time
void DriveToVisionCmd::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveToVisionCmd::Execute() {
	float Kp = 0.1;  // Proportional control constant

	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	float tx = table->GetNumber("tx", 0.0);
	float steering_adjust = Kp*tx;
	drivetrainSub->drive(0.5+steering_adjust, 0.5-steering_adjust);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToVisionCmd::IsFinished() {
	if (drivetrainSub->getLeftEncoder() >= targetDistance){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void DriveToVisionCmd::End() {
	drivetrainSub->drive(0,0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToVisionCmd::Interrupted() {
	End();

}
