#ifndef IntakeSub_H
#define IntakeSub_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "ctre/Phoenix.h"

class IntakeSub : public Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> intakeMotorLeft;
	std::shared_ptr<WPI_TalonSRX> intakeMotorRight;
	std::shared_ptr<WPI_VictorSPX> armFolderMotor;
	std::shared_ptr<DigitalInput> intakeCloseLimit;
	std::shared_ptr<DigitalInput> intakeFarLimit;
	std::shared_ptr<frc::Solenoid> jawOpenSolenoid;
	std::shared_ptr<frc::Solenoid> jawCloseSolenoid;
	std::shared_ptr<frc::Solenoid> mastLights;
	std::shared_ptr<frc::AnalogInput> intakeDistance;
	std::shared_ptr<frc::DigitalInput> armsUpperLimit;

public:
	static constexpr double TIME_TO_LOWER_ARMS = 0.85;

	IntakeSub();
	void InitDefaultCommand();
	void logPeriodicValues();
	void intake(double speed);
	void intake(double leftSpeed, double rightSpeed);
	bool isBoxIn();
	bool isBoxAtJaws();
	void setJawsOpen();
	void setJawsClose();
	void setJawsOnSpring();
	void foldArms(double speed);
	double getBoxDistance();
	bool isArmsUp();
	bool isArmsDown();
	void TurnLightsOn();
};

#endif  // IntakeSub_H
