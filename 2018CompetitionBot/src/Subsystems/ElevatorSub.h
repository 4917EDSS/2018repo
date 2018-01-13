#ifndef ElevatorSub_H
#define ElevatorSub_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "RobotMap.h"

class ElevatorSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<TalonSRX> elevatorMotor;
	std::shared_ptr<frc::Encoder> elevatorMotorEnc;

public:
	ElevatorSub();
	void InitDefaultCommand();
	void setElevatorMotor(float speed);
	double getElevatorEncoder();
	void resetElevatorEncoder();


};

#endif  // ElevatorSub_H
