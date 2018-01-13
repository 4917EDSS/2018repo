#include "DrivetrainSub.h"
#include "../RobotMap.h"
#include "Commands/DriveWithJoystickCmd.h"


DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
	leftMotor1.reset(new TalonSRX(LEFT1_DRIVE_MOTOR_CANID));
	leftMotor2.reset(new TalonSRX(LEFT2_DRIVE_MOTOR_CANID));
	leftMotor3.reset(new TalonSRX(LEFT3_DRIVE_MOTOR_CANID));
	leftMotorEnc.reset(new frc::Encoder(LEFT_MOTOR_ENC1_DIO, LEFT_MOTOR_ENC2_DIO));
	rightMotor1.reset(new TalonSRX(RIGHT1_DRIVE_MOTOR_CANID));
	rightMotor2.reset(new TalonSRX(RIGHT2_DRIVE_MOTOR_CANID));
	rightMotor3.reset(new TalonSRX(RIGHT3_DRIVE_MOTOR_CANID));
	rightMotorEnc.reset(new frc::Encoder(RIGHT_MOTOR_ENC1_DIO, RIGHT_MOTOR_ENC2_DIO));
	driveBalancer.reset(new MotorBalancer());
	distanceBalancer.reset(new MotorBalancer());
	driveBalancePID.reset(new PIDController(1.0, 0.0, 0.0, gyro.get(), driveBalancer.get()));
	driveDistancePID.reset(new PIDController(1.0, 0.0, 0.0, leftMotorEnc.get(), distanceBalancer.get()));
}

double DrivetrainSub::getLeftEncoderSpeed() {
	return leftMotorEnc->GetRate();
}

double DrivetrainSub::getRightEncoderSpeed() {
	return rightMotorEnc->GetRate();
}
double DrivetrainSub::getLeftEncoder()
{
	return leftMotorEnc->GetDistance();
}
double DrivetrainSub::getRightEncoder()
{
	return rightMotorEnc->GetDistance();
}

void DrivetrainSub::drive(double lSpeed, double rSpeed) {
	leftMotor1->Set(ControlMode::PercentOutput, -lSpeed);
	leftMotor2->Set(ControlMode::PercentOutput, -lSpeed);
	leftMotor3->Set(ControlMode::PercentOutput, -lSpeed);
	rightMotor1->Set(ControlMode::PercentOutput, rSpeed);
	rightMotor2->Set(ControlMode::PercentOutput, rSpeed);
	rightMotor3->Set(ControlMode::PercentOutput, rSpeed);
}

void DrivetrainSub::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCmd());
}

void DrivetrainSub::PIDDrive() {
	drive(distanceBalancer->GetDifference() + driveBalancer->GetDifference(), distanceBalancer->GetDifference() - driveBalancer->GetDifference());
}
void DrivetrainSub::resetEncoders() {
	leftMotorEnc->Reset();
	rightMotorEnc->Reset();
}
void DrivetrainSub::enableBalancerPID(float setPoint){
	Preferences *prefs = Preferences::GetInstance();
	driveBalancePID->SetPID(prefs->GetFloat("DriveBalanceP", DRIVE_BALANCE_P), prefs->GetFloat("DriveBalanceI", DRIVE_BALANCE_I), prefs->GetFloat("DriveBalanceD", DRIVE_BALANCE_D));
	driveBalancePID->SetAbsoluteTolerance(prefs->GetFloat("DriveBalanceTolerance", DRIVE_BALANCE_TOLERANCE));
	driveBalancePID->SetSetpoint(setPoint);
	driveBalancer->Reset();
	driveBalancePID->Enable();
}

void DrivetrainSub::disableBalancerPID(){
	driveBalancePID->Disable();
}

void DrivetrainSub::enableDistancePID(float speed, float setPoint){
	Preferences *prefs = Preferences::GetInstance();
	driveDistancePID->SetPID(prefs->GetFloat("DriveDistanceP", DRIVE_DISTANCE_P), prefs->GetFloat("DriveDistanceI", DRIVE_DISTANCE_I), prefs->GetFloat("DriveDistanceD", DRIVE_DISTANCE_D));
	driveDistancePID->SetAbsoluteTolerance(prefs->GetFloat("DriveDistanceTolerance", DRIVE_DISTANCE_TOLERANCE));
	driveDistancePID->SetSetpoint(setPoint);
	driveDistancePID->SetOutputRange(-speed, speed);
	distanceBalancer->Reset();
	driveDistancePID->Enable();
}
void DrivetrainSub::disableDistancePID(){
	driveDistancePID->Disable();
}




// Put methods for controlling this subsystem
// here. Call these from Commands.
