#ifndef IntakeSub_H
#define IntakeSub_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/Phoenix.h"

class IntakeSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<TalonSRX> intakeMotor;
	std::shared_ptr<DigitalInput> intakeLimit;

public:
	IntakeSub();
	void InitDefaultCommand();
	void intake(double speed);
	bool IsLimitHit();
};

#endif  // IntakeSub_H
