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
constexpr float DRIVE_TURN_P = 0.032;
constexpr float DRIVE_TURN_I = 0.0;
constexpr float DRIVE_TURN_D = 0.019;

DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
	// Initialize the hardware
	// Make sure to SetName in order to enable diagnostics view LiveWindow
	leftMotor1.reset(new WPI_VictorSPX(DRIVE_MOTOR_LEFT1_CANID));
	leftMotor1->SetName("Drivetrain", "Left Motor 1");
	leftMotor2.reset(new WPI_VictorSPX(DRIVE_MOTOR_LEFT2_CANID));
	leftMotor2->SetName("Drivetrain", "Left Motor 2");
	leftMotor3.reset(new WPI_VictorSPX(DRIVE_MOTOR_LEFT3_CANID));
	leftMotor3->SetName("Drivetrain", "Left Motor 3");

	rightMotor1.reset(new WPI_VictorSPX(DRIVE_MOTOR_RIGHT1_CANID));
	rightMotor1->SetName("Drivetrain", "Right Motor 1");
	rightMotor2.reset(new WPI_VictorSPX(DRIVE_MOTOR_RIGHT2_CANID));
	rightMotor2->SetName("Drivetrain", "Right Motor 2");
	rightMotor3.reset(new WPI_VictorSPX(DRIVE_MOTOR_RIGHT3_CANID));
	rightMotor3->SetName("Drivetrain", "Right Motor 3");

	leftMotorEnc.reset(new frc::Encoder(DRIVE_MOTOR_LEFT_ENC1_DIO, DRIVE_MOTOR_LEFT_ENC2_DIO));
	leftMotorEnc->SetName("Drivetrain", "Left Motor Enc");
	leftMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE * 4);

	rightMotorEnc.reset(new frc::Encoder(DRIVE_MOTOR_RIGHT_ENC1_DIO, DRIVE_MOTOR_RIGHT_ENC2_DIO));
	rightMotorEnc->SetName("Drivetrain", "Right Motor Enc");
	rightMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE * 4);

	ahrs.reset(new AHRS(AHRSInterface));
	ahrs->SetName("Drivetrain", "AHRS");

	shifters.reset(new frc::Solenoid(SHIFTERS_PCM_ID));
	shifters->SetName("Drivetrain", "Shifter");
	setLowGear();

	frontRangefinder.reset(new frc::Ultrasonic(DRIVETRAIN_FRONT_ULTRASONIC_TRIG_DIO, DRIVETRAIN_FRONT_ULTRASONIC_ECHO_DIO, frc::Ultrasonic::kMilliMeters));
	frontRangefinder->SetName("Drivetrain", "Front Rangefinder");
	frontRangefinder->SetAutomaticMode(false);

	rearRangefinder.reset(new AnalogInput(DRIVETRAIN_REAR_ULTRASONIC_AI));
	rearRangefinder->SetName("Drivetrain", "Rear Rangefinder");

	// Initialize software controllers
	turnBalancer.reset(new MotorBalancer());
	driveBalancer.reset(new MotorBalancer());
	distanceBalancer.reset(new MotorBalancer());

	driveBalancePID.reset(new PIDController(DRIVE_BALANCE_P, DRIVE_BALANCE_I, DRIVE_BALANCE_D, ahrs.get(), driveBalancer.get()));
	driveDistancePID.reset(new PIDController(DRIVE_DISTANCE_P, DRIVE_DISTANCE_I, DRIVE_DISTANCE_D, leftMotorEnc.get(), distanceBalancer.get()));
	Preferences *prefs = Preferences::GetInstance();
	driveTurnPID.reset(new frc::PIDController(prefs->GetFloat("DriveTurnP", DRIVE_TURN_P),
				   	   	   	   	   	   	   	  prefs->GetFloat("DriveTurnI", DRIVE_TURN_I),
											  prefs->GetFloat("DriveTurnD", DRIVE_TURN_D),
											  ahrs.get(),
											  turnBalancer.get()));
}


void DrivetrainSub::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCmd());
}

void DrivetrainSub::logPeriodicValues() {
	// Prefix the line with "LP:" for log-periodic so we can filter on that
	// Use commas to separate fields to make it easy to import into a spreadsheet
	logger.send(logger.PERIODIC, "%d,LP:Drivetrain,"
			"Motor Percent,L1,%f,L2,%f,L3,%f,R1,%f,R2,%f,R3,%f,"
			"Motor Currents,L1,%f,L2,%f,L3,%f,R1,%f,R2,%f,R3,%f,"
			"Motor Encoder,L,%d,R,%d,LRaw,%d,RRaw,%d,"
			"AHRS,Yaw,%f,Pitch,%f,Roll,%f,"
			"Shifter,%d,"
			"Distance,Front,%f,Rear,%d,"
			"\n",
			(uint32_t)(frc::RobotController::GetFPGATime() & 0xFFFFFFFF),
			leftMotor1->GetMotorOutputPercent(), leftMotor2->GetMotorOutputPercent(), leftMotor3->GetMotorOutputPercent(),
			rightMotor1->GetMotorOutputPercent(), rightMotor2->GetMotorOutputPercent(), rightMotor3->GetMotorOutputPercent(),
			leftMotor1->GetOutputCurrent(), leftMotor2->GetOutputCurrent(), leftMotor3->GetOutputCurrent(),
			rightMotor1->GetOutputCurrent(), rightMotor2->GetOutputCurrent(), rightMotor3->GetOutputCurrent(),
			leftMotorEnc->Get(), rightMotorEnc->Get(), leftMotorEnc->GetRaw(), rightMotorEnc->GetRaw(),
			ahrs->GetYaw(), ahrs->GetPitch(),ahrs->GetRoll(),
			shifters->Get() ? 1 : 0,
			frontRangefinder->GetRangeMM(),	rearRangefinder->GetValue()
			);

	// Can add additional or easier-to-read periodic logging here
//	logger.send(logger.PERIODIC, "$Front Rangefinder = %f\n", frontRangefinder->GetRangeMM() );
	return;
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

void DrivetrainSub::PIDWallTurn() {
	drive(turnBalancer->GetDifference(), -turnBalancer->GetDifference());
	if (turnBalancer->GetDifference() > 0.0 ){
		drive(turnBalancer->GetDifference()*1.5,0);
	}
	else if (turnBalancer->GetDifference() <0.0){
		drive(0, -turnBalancer->GetDifference()*1.5);
	}
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

void DrivetrainSub::setHighGear() {
	shifters->Set(true);
}

void DrivetrainSub::setLowGear() {
	shifters->Set(false);
}

void DrivetrainSub::enableFrontRangefinder(bool enable) {
	frontRangefinder->SetAutomaticMode(enable);
}

double DrivetrainSub::getFrontRangefinderDist() {
	return frontRangefinder->GetRangeMM();
}

