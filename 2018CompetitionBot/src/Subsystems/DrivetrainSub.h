#ifndef DrivetrainSub_H
#define DrivetrainSub_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "Components/MotorBalancer.h"
#include "ctre/Phoenix.h"
#include "RobotMap.h"
#include "AHRS.h"

class DrivetrainSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	const float DRIVETRAIN_DIS_PER_PULSE = 2000.0/4975.0;
	std::shared_ptr<TalonSRX> leftMotor1;
	std::shared_ptr<TalonSRX> leftMotor2;
	std::shared_ptr<TalonSRX> leftMotor3;
	std::shared_ptr<TalonSRX> rightMotor1;
	std::shared_ptr<TalonSRX> rightMotor2;
	std::shared_ptr<TalonSRX> rightMotor3;
	std::shared_ptr<frc::Encoder> leftMotorEnc;
	std::shared_ptr<frc::Encoder> rightMotorEnc;
	std::shared_ptr<AHRS> ahrs;
	std::shared_ptr<MotorBalancer> turnBalancer;
	std::shared_ptr<MotorBalancer> driveBalancer;
	std::shared_ptr<MotorBalancer> distanceBalancer;
	std::shared_ptr<frc::PIDController> driveTurnPID;
	std::shared_ptr<frc::PIDController> driveBalancePID;
	std::shared_ptr<frc::PIDController> driveDistancePID;
	std::shared_ptr<frc::Ultrasonic> hcsr04;

public:

	DrivetrainSub();
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
	void enableFrontUltrasonic(bool enable);
	double getFrontUltrasonicDist();
};

#endif  // DrivetrainSub_H
