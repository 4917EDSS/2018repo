#ifndef DrivetrainSub_H
#define DrivetrainSub_H

#include <Commands/Subsystem.h>
#include <CANTalon.h>
#include <WPILib.h>

#define SOLENOID_HIGH_GEAR	frc::DoubleSolenoid::kForward
#define SOLENOID_LOW_GEAR	frc::DoubleSolenoid::kReverse

class DrivetrainSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> leftMotor1;
	std::shared_ptr<CANTalon> leftMotor2;
	std::shared_ptr<CANTalon> leftMotor3;
	std::shared_ptr<CANTalon> rightMotor1;
	std::shared_ptr<CANTalon> rightMotor2;
	std::shared_ptr<CANTalon> rightMotor3;
	std::shared_ptr<frc::Encoder> leftMotorEnc;
	std::shared_ptr<frc::Encoder> rightMotorEnc;
	std::shared_ptr<frc::DoubleSolenoid> shifter;
	bool highGear;
	double shiftHighSpeed;
	double shiftLowSpeed;

public:
	DrivetrainSub();
	void InitDefaultCommand();
	void initHardware();
	void drive(double lPower, double rPower);
	void setShifter(frc::DoubleSolenoid::Value shiftState);

	bool isInHighGear();
	double getLeftEncoderRaw();
	double getRightEncoderRaw();
	double getLeftEncoder();
	double getRightEncoder();
	double getLeftEncoderSpeed();
	double getRightEncoderSpeed();
};

#endif  // DrivetrainSub_H
