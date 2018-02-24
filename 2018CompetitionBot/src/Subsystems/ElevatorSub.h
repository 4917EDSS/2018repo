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
	std::shared_ptr<Ultrasonic> tinyLidar;
	double target;
	bool finishedMove;
	double lastLidarValue;

public:
	static constexpr double SCALE_BOX_HIGH_HEIGHT = 626.75;
	static constexpr double SCALE_BOX_MEDIUM_HEIGHT = 548.75;
	static constexpr double SCALE_BOX_LOW_HEIGHT = 470.75;
	static constexpr double SWITCH_BOX_HEIGHT = 216.5;
	static constexpr double MAX_HEIGHT = 625;
	ElevatorSub();
	void InitDefaultCommand();
	void setElevatorMotor(double speed);
	double getElevatorEncoder();
	void setElevatorMotorRaw(double speed);
	void resetElevatorEncoder();
	void elevatorMotorUp();
	void elevatorMotorDown();
	void update();
	void setTarget(double newTarget);
	void startTinyLidar();
	double getLidarValue();
	void endTinyLidar();
	bool isAtMaxDropHeight();
	bool atScaleHeight();
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
