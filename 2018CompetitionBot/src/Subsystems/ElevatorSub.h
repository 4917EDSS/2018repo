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
	std::shared_ptr<TalonSRX> elevatorMotor1;
	std::shared_ptr<TalonSRX> elevatorMotor2;
	std::shared_ptr<frc::Encoder> elevatorMotorEnc;
//	std::shared_ptr<frc::PIDController> liftPID;
	std::shared_ptr<DigitalInput> lowerLimit;

	double target;
	bool finishedMove;

public:
	ElevatorSub();
	void InitDefaultCommand();
	void setElevatorMotor(float speed);
	double getElevatorEncoder();
	void resetElevatorEncoder();
	void elevatorMotorUp();
	void elevatorMotorDown();
	void update();
	void setTarget(int newTarget);
//	void enableLiftPID(float setPoint);
//	void disableLiftPID();
//	bool PIDLiftIsFinished();
	bool isElevatorDown();
	double convertHeightToEncoder(double cm);
	bool isFinishedMove() {
		return finishedMove;
	}
};

#endif  // ElevatorSub_H
