#ifndef LiftSub_H
#define LiftSub_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "RobotMap.h"

class LiftSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<TalonSRX> rampMotor1;
	std::shared_ptr<TalonSRX> rampMotor2;
	std::shared_ptr<TalonSRX> liftMotor1;
	std::shared_ptr<DigitalInput> rampLimit;
	std::shared_ptr<DigitalInput> extentionLimit;

public:
	LiftSub();
	void InitDefaultCommand();
	void LiftSub::lowerRamp();
	void LiftSub::extendRamp();
	void LiftSub::raiseLift();
	void LiftSub::stopRamp();
	void LiftSub::stopLift();
	bool LiftSub::isRampLowered();
	bool LiftSub::isRampExtended();
};

#endif  // LiftSub_H
