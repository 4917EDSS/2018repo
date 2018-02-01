#ifndef IntakeSub_H
#define IntakeSub_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "ctre/Phoenix.h"

class IntakeSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<TalonSRX> intakeMotorLeft;
	std::shared_ptr<TalonSRX> intakeMotorRight;
	std::shared_ptr<DigitalInput> intakeLimit;
	std::shared_ptr<frc::DoubleSolenoid> jaws;
	std::shared_ptr<frc::Ultrasonic> hcsr04;

public:
	IntakeSub();
	void InitDefaultCommand();
	void intake(double speed);
	void intake(double leftSpeed, double rightSpeed);
	bool IsLimitHit();
	void enableFrontUltrasonic(bool enable);
	double getFrontUltrasonicDist();
};

#endif  // IntakeSub_H
