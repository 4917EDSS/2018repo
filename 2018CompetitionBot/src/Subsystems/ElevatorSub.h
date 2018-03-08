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
	std::shared_ptr<WPI_TalonSRX> elevatorMotor1;
	std::shared_ptr<WPI_TalonSRX> elevatorMotor2;
	std::shared_ptr<frc::Encoder> elevatorMotorEnc;
	std::shared_ptr<frc::DigitalInput> lowerLimit;
	std::shared_ptr<frc::Ultrasonic> rangefinder;
	std::shared_ptr<frc::Solenoid> climbBarSolenoid;
	double target;
	bool finishedMove;
	double lastLidarValue;

public:
	static constexpr double SCALE_BOX_HIGH_HEIGHT = 626.75;
	static constexpr double SCALE_BOX_MEDIUM_HEIGHT = 555;
	static constexpr double SCALE_BOX_LOW_HEIGHT = 500;
	static constexpr double SWITCH_BOX_HEIGHT = 216.5;
	static constexpr double MAX_ELEVATOR_HEIGHT = 625;
	static constexpr double CARRY_HEIGHT = 20;
	ElevatorSub();
	void InitDefaultCommand();
	void logPeriodicValues();
	void setElevatorMotor(double speed);
	double getElevatorEncoder();
	void setElevatorMotorRaw(double speed);
	void resetElevatorEncoder();
	void elevatorMotorUp();
	void elevatorMotorDown();
	void update();
	void setTarget(double newTarget);
	void startRangefinder();
	double getRangfinderDist();
	void stopRangefinder();
	bool isAtMaxDropHeight();
	bool atScaleHeight();
	bool isElevatorDown();
	double convertHeightToEncoder(double cm);
	bool isFinishedMove();
	void extendClimbBar();
};

#endif  // ElevatorSub_H
