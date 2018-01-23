#include "IntakeSub.h"
#include "../RobotMap.h"

IntakeSub::IntakeSub() : Subsystem("IntakeSub") {
	intakeMotor.reset(new TalonSRX(INTAKE_MOTOR_CANID));
	intakeLimit.reset(new DigitalInput(INTAKE_LIMIT_SWITCH_DIO));
	compressors.reset(new frc::DoubleSolenoid(COMPRESSORS_PCM_ID1, COMPRESSORS_PCM_ID2));
	hcsr04.reset(new frc::Ultrasonic(DRIVE_TRAIN_ULTRASONIC_TRIG_DIO, DRIVE_TRAIN_ULTRASONIC_ECHO_DIO, frc::Ultrasonic::kMilliMeters));

//	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
//	lw->AddActuator("Intake", "Compressor Solenoid", compressors);
}
//
void IntakeSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void IntakeSub::intake(double speed) {
	intakeMotor->Set(ControlMode::PercentOutput, speed);
}

void IntakeSub::openCompressor() {
	if(compressorsEnabled) {
		compressors->Set(frc::DoubleSolenoid::Value::kForward);
	}
}

void IntakeSub::closeCompressor() {
	if(compressorsEnabled) {
		compressors->Set(frc::DoubleSolenoid::Value::kReverse);
	}
}

bool IntakeSub::IsLimitHit() {
	return !intakeLimit->Get();
}

void IntakeSub::enableFrontUltrasonic(bool enable){
	hcsr04->SetAutomaticMode(enable);
}

double IntakeSub::getFrontUltrasonicDist(){
	return hcsr04->GetRangeMM();
}
