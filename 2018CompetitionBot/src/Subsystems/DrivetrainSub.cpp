#include "DrivetrainSub.h"
#include "../RobotMap.h"
#include "Commands/DriveWithJoystickCmd.h"
#include <iostream>
#include <sstream>

constexpr float DRIVE_BALANCE_TOLERANCE = 0.5;

constexpr float DRIVE_BALANCE_P = 0.018;
constexpr float DRIVE_BALANCE_I = 0.0;
constexpr float DRIVE_BALANCE_D = 0.0;
constexpr float DRIVE_DISTANCE_P = 0.004;
constexpr float DRIVE_DISTANCE_I = 0.0;
constexpr float DRIVE_DISTANCE_D = 0.002;
constexpr float DRIVE_TURN_P = 0.03;
constexpr float DRIVE_TURN_I = 0.0;
constexpr float DRIVE_TURN_D = 0.017;

DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
	leftMotor1.reset(new VictorSPX(DRIVE_MOTOR_LEFT1_CANID));
	leftMotor2.reset(new VictorSPX(DRIVE_MOTOR_LEFT2_CANID));
	leftMotor3.reset(new VictorSPX(DRIVE_MOTOR_LEFT3_CANID));
	rightMotor1.reset(new VictorSPX(DRIVE_MOTOR_RIGHT1_CANID));
	rightMotor2.reset(new VictorSPX(DRIVE_MOTOR_RIGHT2_CANID));
	rightMotor3.reset(new VictorSPX(DRIVE_MOTOR_RIGHT3_CANID));
	rightMotorEnc.reset(new frc::Encoder(DRIVE_MOTOR_RIGHT_ENC1_DIO, DRIVE_MOTOR_RIGHT_ENC2_DIO));
	leftMotorEnc.reset(new frc::Encoder(DRIVE_MOTOR_LEFT_ENC1_DIO, DRIVE_MOTOR_LEFT_ENC2_DIO));
	leftMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE * 4);
	rightMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE * 4);
	//frontUltrasonic.reset(new frc::Ultrasonic(DRIVETRAIN_FRONT_ULTRASONIC_TRIG_DIO, DRIVETRAIN_FRONT_ULTRASONIC_ECHO_DIO, frc::Ultrasonic::kMilliMeters));

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
	shifters.reset(new frc::Solenoid(SHIFTERS_PCM_ID));
	setLowGear();
}

double DrivetrainSub::getLeftEncoderSpeed() {
	return leftMotorEnc->GetRate();
}

double DrivetrainSub::getRightEncoderSpeed() {
	return rightMotorEnc->GetRate();
}

double DrivetrainSub::getLeftEncoder() {
	return leftMotorEnc->GetDistance();
}

double DrivetrainSub::getRightEncoder() {
	return rightMotorEnc->GetDistance();
}

void DrivetrainSub::drive(double lSpeed, double rSpeed) {
	leftMotor1->Set(ControlMode::PercentOutput, lSpeed);
	leftMotor2->Set(ControlMode::PercentOutput, -lSpeed);
	leftMotor3->Set(ControlMode::PercentOutput, lSpeed);
	rightMotor1->Set(ControlMode::PercentOutput, -rSpeed);
	rightMotor2->Set(ControlMode::PercentOutput, rSpeed);
	rightMotor3->Set(ControlMode::PercentOutput, -rSpeed);
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

void DrivetrainSub::enableBalancerPID(float setPoint) {
	Preferences *prefs = Preferences::GetInstance();
	driveBalancePID->SetPID(prefs->GetFloat("DriveBalanceP", DRIVE_BALANCE_P), prefs->GetFloat("DriveBalanceI", DRIVE_BALANCE_I), prefs->GetFloat("DriveBalanceD", DRIVE_BALANCE_D));
	driveBalancePID->SetAbsoluteTolerance(prefs->GetFloat("DriveBalanceTolerance", DRIVE_BALANCE_TOLERANCE));
	driveBalancePID->SetSetpoint(setPoint);
	driveBalancer->Reset();
	driveBalancePID->Enable();
}

void DrivetrainSub::disableBalancerPID() {
	distanceBalancer->Reset();
	driveBalancePID->Disable();
}

void DrivetrainSub::enableDistancePID(float speed, float setPoint) {
	Preferences *prefs = Preferences::GetInstance();
	driveDistancePID->SetPID(prefs->GetFloat("DriveDistanceP", DRIVE_DISTANCE_P), prefs->GetFloat("DriveDistanceI", DRIVE_DISTANCE_I), prefs->GetFloat("DriveDistanceD", DRIVE_DISTANCE_D));
	driveDistancePID->SetAbsoluteTolerance(prefs->GetFloat("DriveDistanceTolerance", DRIVE_DISTANCE_TOLERANCE));
	driveDistancePID->SetSetpoint(setPoint);
	driveDistancePID->SetOutputRange(-speed, speed);
	distanceBalancer->Reset();
	driveDistancePID->Enable();
}

void DrivetrainSub::disableDistancePID() {
	driveDistancePID->Disable();
}

// PIDTurn functions
void DrivetrainSub::enableTurnPID(double setPoint) {
	Preferences *prefs = Preferences::GetInstance();
	driveTurnPID->SetPID(prefs->GetFloat("DriveTurnP", DRIVE_TURN_P), prefs->GetFloat("DriveTurnI", DRIVE_TURN_I), prefs->GetFloat("DriveTurnD", DRIVE_TURN_D));
	driveTurnPID->SetAbsoluteTolerance(prefs->GetFloat("DriveTurnTolerance", DRIVE_TURN_TOLERANCE));
	driveTurnPID->SetSetpoint(setPoint);
	driveTurnPID->Enable();
}

void DrivetrainSub::disableTurnPID() {
	driveTurnPID->Disable();
}

void DrivetrainSub::PIDTurn() {
	drive(turnBalancer->GetDifference(), -turnBalancer->GetDifference());
}

bool DrivetrainSub::isTurnFinished() {
	return driveTurnPID->OnTarget();
}

void DrivetrainSub::resetAHRS() {
	ahrs->Reset();
}

double DrivetrainSub::getAngle() {
	return ahrs->GetAngle();
}

double DrivetrainSub::getRate() {
	return ahrs->GetRate();
}

void DrivetrainSub::driverDriveStraight(float speed) {
	drive(speed + driveBalancer->GetDifference(), speed - driveBalancer->GetDifference());
}

void DrivetrainSub::enableFrontUltrasonic(bool enable) {
	//frontUltrasonic->SetAutomaticMode(enable);
}

double DrivetrainSub::getFrontUltrasonicDist() {
	return 0.0;//frontUltrasonic->GetRangeMM();
}

void DrivetrainSub::setHighGear() {
	shifters->Set(true);
}

void DrivetrainSub::setLowGear() {
	shifters->Set(false);
}

