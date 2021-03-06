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
	std::shared_ptr<WPI_VictorSPX> elevatorMotor3;
	std::shared_ptr<WPI_VictorSPX> elevatorMotor4;
	std::shared_ptr<frc::Encoder> elevatorMotorEnc;
	std::shared_ptr<frc::DigitalInput> lowerLimit;
	std::shared_ptr<frc::Ultrasonic> rangefinder;
	std::shared_ptr<frc::Solenoid> climbBarSolenoid;
	std::shared_ptr<frc::Solenoid> climbBarInSolenoid;
	double target;
	double lastLidarValue;
	bool isDoneFirstRangefinder;
	double lastRangefinderValue;
	int debounceCounter;
	void storeNewRangefinderValue(double distance);

public:
	static constexpr double AUTO_FIRST_BOX_HEIGHT = 680.00;
	static constexpr double SCALE_BOX_HIGH_HEIGHT = 666.00;
	static constexpr double SCALE_BOX_MEDIUM_HEIGHT = 573.00;
	static constexpr double SCALE_BOX_LOW_HEIGHT = 480.00;
	static constexpr double SWITCH_BOX_HEIGHT = 250.00;
	static constexpr double MAX_ELEVATOR_HEIGHT = 728;
	static constexpr double CLIMB_HEIGHT = 515.25;
	static constexpr double CARRY_HEIGHT = 20;
	ElevatorSub();
	void init();
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
	void retractClimbBar();
	void setClimbBarNeutral();
	void updateSensorsPeriodic();
	double getFilteredRangefinderValue();
	double getRawRangefinderValue();
};

#endif  // ElevatorSub_H
