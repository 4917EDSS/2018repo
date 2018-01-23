#include "DrivetrainSub.h"
#include "../RobotMap.h"
#include "Commands/DriveWithJoystickCmd.h"
#include <iostream>

constexpr float DRIVE_BALANCE_P = 0.018;
constexpr float DRIVE_BALANCE_I = 0.0;
constexpr float DRIVE_BALANCE_D = 0.0;
constexpr float DRIVE_DISTANCE_P = 0.009;
constexpr float DRIVE_DISTANCE_I = 0.0;
constexpr float DRIVE_DISTANCE_D = 0.001;
constexpr float DRIVE_TURN_P = 0.0228;
constexpr float DRIVE_TURN_I = 0.0;
constexpr float DRIVE_TURN_D = 0.02;

DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
	leftMotor1.reset(new TalonSRX(LEFT1_DRIVE_MOTOR_CANID));
	leftMotor2.reset(new TalonSRX(LEFT2_DRIVE_MOTOR_CANID));
	leftMotor3.reset(new TalonSRX(LEFT3_DRIVE_MOTOR_CANID));
	rightMotor1.reset(new TalonSRX(RIGHT1_DRIVE_MOTOR_CANID));
	rightMotor2.reset(new TalonSRX(RIGHT2_DRIVE_MOTOR_CANID));
	rightMotor3.reset(new TalonSRX(RIGHT3_DRIVE_MOTOR_CANID));
	rightMotorEnc.reset(new frc::Encoder(RIGHT_MOTOR_ENC1_DIO, RIGHT_MOTOR_ENC2_DIO));
	leftMotorEnc.reset(new frc::Encoder(LEFT_MOTOR_ENC1_DIO, LEFT_MOTOR_ENC2_DIO));
	leftMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE * 4);
	rightMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE * 4);
	hcsr04.reset(new frc::Ultrasonic(DRIVE_TRAIN_ULTRASONIC_TRIG_DIO, DRIVE_TRAIN_ULTRASONIC_ECHO_DIO, frc::Ultrasonic::kMilliMeters));

	turnBalancer.reset(new MotorBalancer());
	driveBalancer.reset(new MotorBalancer());
	distanceBalancer.reset(new MotorBalancer());
	ahrs.reset(new AHRS(AHRSInterface));
	driveBalancePID.reset(new PIDController(DRIVE_BALANCE_P, DRIVE_BALANCE_I, DRIVE_BALANCE_D, ahrs.get(), driveBalancer.get()));
	driveDistancePID.reset(new PIDController(DRIVE_DISTANCE_P, DRIVE_DISTANCE_I, DRIVE_DISTANCE_D, leftMotorEnc.get(), distanceBalancer.get()));
	Preferences *prefs = Preferences::GetInstance();
	driveTurnPID.reset(new frc::PIDController(prefs->GetFloat("DriveTurnP", DRIVE_TURN_P),
				   	   	   	   	   	   	   	  prefs->GetFloat("DriveTurnI", DRIVE_TURN_I),
											  prefs->GetFloat("DriveTurnD", DRIVE_TURN_D),
											  ahrs.get(),
											  turnBalancer.get()));
	shifters.reset(new frc::DoubleSolenoid(SHIFTERS_PCM1, SHIFTERS_PCM2));

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
	leftMotor1->Set(ControlMode::PercentOutput, lSpeed);
	leftMotor2->Set(ControlMode::PercentOutput, lSpeed);
	leftMotor3->Set(ControlMode::PercentOutput, lSpeed);
	rightMotor1->Set(ControlMode::PercentOutput, -rSpeed);
	rightMotor2->Set(ControlMode::PercentOutput, -rSpeed);
	rightMotor3->Set(ControlMode::PercentOutput, -rSpeed);
}

void DrivetrainSub::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCmd());
}

void DrivetrainSub::PIDDrive() {
	std::cout<<ahrs->GetYaw()<<std::endl;
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

// PIDTurn functions
void DrivetrainSub::enableTurnPID(double setPoint){
	Preferences *prefs = Preferences::GetInstance();
	driveTurnPID->SetPID(prefs->GetFloat("DriveTurnP", DRIVE_TURN_P), prefs->GetFloat("DriveTurnI", DRIVE_TURN_I), prefs->GetFloat("DriveTurnD", DRIVE_TURN_D));
	driveTurnPID->SetAbsoluteTolerance(prefs->GetFloat("DriveTurnTolerance", DRIVE_TURN_TOLERANCE));
	driveTurnPID->SetSetpoint(setPoint);
	driveTurnPID->Enable();
}
void DrivetrainSub::disableTurnPID(){
	driveTurnPID->Disable();
}
void DrivetrainSub::PIDTurn(){
	leftMotor1->Set(ControlMode::PercentOutput, turnBalancer->GetDifference());
	leftMotor2->Set(ControlMode::PercentOutput, turnBalancer->GetDifference());
	leftMotor3->Set(ControlMode::PercentOutput, turnBalancer->GetDifference());
	rightMotor1->Set(ControlMode::PercentOutput, turnBalancer->GetDifference());
	rightMotor2->Set(ControlMode::PercentOutput, turnBalancer->GetDifference());
	rightMotor3->Set(ControlMode::PercentOutput, turnBalancer->GetDifference());
}
bool DrivetrainSub::isTurnFinished(){
	return driveTurnPID->OnTarget();
}

void DrivetrainSub::resetAHRS(){
	ahrs->ZeroYaw();
}

double DrivetrainSub::getAngle(){
	return ahrs->GetAngle();
}

double DrivetrainSub::getRate(){
	return ahrs->GetRate();
}

void DrivetrainSub::driverDriveStraight(float speed){
	drive(speed + driveBalancer->GetDifference(), speed - driveBalancer->GetDifference());
}

void DrivetrainSub::enableFrontUltrasonic(bool enable){
	hcsr04->SetAutomaticMode(enable);
}

double DrivetrainSub::getFrontUltrasonicDist(){
	return hcsr04->GetRangeMM();
}
void DrivetrainSub::setHighGear() {
	shifters->Set(frc::DoubleSolenoid::Value::kReverse);
}

void DrivetrainSub::setLowGear() {
	shifters->Set(frc::DoubleSolenoid::Value::kForward);
}
