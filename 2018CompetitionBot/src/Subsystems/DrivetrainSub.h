#ifndef DrivetrainSub_H
#define DrivetrainSub_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "Components/MotorBalancer.h"
#include "ctre/Phoenix.h"
#include "RobotMap.h"
#include "AHRS.h"

constexpr float DRIVE_DISTANCE_TOLERANCE = 15.0;
constexpr float DISTANCE_SPEED_TOLERANCE = 10.0;
constexpr float DRIVE_TURN_TOLERANCE = 2.0;
constexpr float DRIVE_RATE_TOLERANCE = 1;

class DrivetrainSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	const float DRIVETRAIN_DIS_PER_PULSE = 3000.0/6150.0;
	std::shared_ptr<VictorSPX> leftMotor1;
	std::shared_ptr<VictorSPX> leftMotor2;
	std::shared_ptr<VictorSPX> leftMotor3;
	std::shared_ptr<VictorSPX> rightMotor1;
	std::shared_ptr<VictorSPX> rightMotor2;
	std::shared_ptr<VictorSPX> rightMotor3;
	std::shared_ptr<frc::Encoder> leftMotorEnc;
	std::shared_ptr<frc::Encoder> rightMotorEnc;
	std::shared_ptr<AHRS> ahrs;
	std::shared_ptr<MotorBalancer> turnBalancer;
	std::shared_ptr<MotorBalancer> driveBalancer;
	std::shared_ptr<MotorBalancer> distanceBalancer;
	std::shared_ptr<frc::PIDController> driveTurnPID;
	std::shared_ptr<frc::PIDController> driveBalancePID;
	std::shared_ptr<frc::PIDController> driveDistancePID;
	std::shared_ptr<frc::Ultrasonic> frontRangefinder;
	std::shared_ptr<frc::AnalogInput> rearRangefinder;
	std::shared_ptr<frc::Solenoid> shifters;

public:
	DrivetrainSub();
	void logPeriodicValues();
	double getLeftEncoder();
	double getRightEncoder();
	double getLeftEncoderSpeed();
	double getRightEncoderSpeed();
	void InitDefaultCommand();
	void drive( double lSpeed, double rSpeed );
	void disableBalancerPID();
	void disableDistancePID();
	void PIDDrive();
	void resetEncoders();
	void enableBalancerPID(float setPoint);
	void enableDistancePID(float speed, float setPoint);
	void enableTurnPID(double setPoint);
	void disableTurnPID();
	void PIDTurn();
	bool isTurnFinished();
	void resetAHRS();
	double getAngle();
	double getRate();
	void driverDriveStraight(float speed);
	void enableFrontRangefinder(bool enable);
	double getFrontUltrasonicDist();
	void setHighGear();
	void setLowGear();
};

#endif  // DrivetrainSub_H
