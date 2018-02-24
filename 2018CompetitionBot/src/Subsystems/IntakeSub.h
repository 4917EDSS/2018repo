#ifndef IntakeSub_H
#define IntakeSub_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "ctre/Phoenix.h"

class IntakeSub : public Subsystem {
private:
	std::shared_ptr<TalonSRX> intakeMotorLeft;
	std::shared_ptr<TalonSRX> intakeMotorRight;
	std::shared_ptr<DigitalInput> intakeCloseLimit;
	std::shared_ptr<DigitalInput> intakeFarLimit;
	std::shared_ptr<frc::Solenoid> jawOpenSolenoid;
	std::shared_ptr<frc::Solenoid> jawCloseSolenoid;
	std::shared_ptr<frc::Ultrasonic> hcsr04;
	std::shared_ptr<frc::AnalogInput> intakeDistance;

public:
	IntakeSub();
	void InitDefaultCommand();
	void intake(double speed);
	void intake(double leftSpeed, double rightSpeed);
	bool isBoxIn();
	bool isBoxAtJaws();
	void enableFrontUltrasonic(bool enable);
	double getFrontUltrasonicDist();
	void setJawsOpen();
	void setJawsClose();
	void setJawsOnSpring();
	double getBoxDistance();
};

#endif  // IntakeSub_H
