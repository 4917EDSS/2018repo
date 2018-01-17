#include "DrivetrainSub.h"
#include "../RobotMap.h"
#include "Commands/DriveWithJoystickCmd.h"

constexpr float DRIVE_BALANCE_P = 1.0;
constexpr float DRIVE_BALANCE_I = 0.0;
constexpr float DRIVE_BALANCE_D = 0.0;
constexpr float DRIVE_DISTANCE_P = 1.0;
constexpr float DRIVE_DISTANCE_I = 0.0;
constexpr float DRIVE_DISTANCE_D = 0.0;
constexpr float DRIVE_TURN_P = 0.1;
constexpr float DRIVE_TURN_I = 0.001;
constexpr float DRIVE_TURN_D = 0.0;

DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
	leftMotor1.reset(new TalonSRX(LEFT1_DRIVE_MOTOR_CANID));
	leftMotor2.reset(new TalonSRX(LEFT2_DRIVE_MOTOR_CANID));
	leftMotor3.reset(new TalonSRX(LEFT3_DRIVE_MOTOR_CANID));
	leftMotorEnc.reset(new frc::Encoder(LEFT_MOTOR_ENC1_DIO, LEFT_MOTOR_ENC2_DIO));
	rightMotor1.reset(new TalonSRX(RIGHT1_DRIVE_MOTOR_CANID));
	rightMotor2.reset(new TalonSRX(RIGHT2_DRIVE_MOTOR_CANID));
	rightMotor3.reset(new TalonSRX(RIGHT3_DRIVE_MOTOR_CANID));
	rightMotorEnc.reset(new frc::Encoder(RIGHT_MOTOR_ENC1_DIO, RIGHT_MOTOR_ENC2_DIO));
	turnBalancer.reset(new MotorBalancer());
	driveBalancer.reset(new MotorBalancer());
	distanceBalancer.reset(new MotorBalancer());
	ahrs.reset(new AHRS(AHRSInterface));
	driveBalancePID.reset(new PIDController(1.0, 0.0, 0.0, gyro.get(), driveBalancer.get()));
	driveDistancePID.reset(new PIDController(1.0, 0.0, 0.0, leftMotorEnc.get(), distanceBalancer.get()));
	Preferences *prefs = Preferences::GetInstance();
	driveTurnPID.reset(new frc::PIDController(prefs->GetFloat("DriveTurnP", DRIVE_TURN_P),
				   	   	   	   	   	   	   	  prefs->GetFloat("DriveTurnI", DRIVE_TURN_I),
											  prefs->GetFloat("DriveTurnD", DRIVE_TURN_D),
											  ahrs.get(),
											  turnBalancer.get()));

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

// Put methods for controlling this subsystem
// here. Call these from Commands.
