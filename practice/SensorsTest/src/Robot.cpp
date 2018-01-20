/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <WPILib.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <I2C.h>

#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"

class Robot : public frc::TimedRobot {
public:
	void RobotInit() override {
		m_chooser.AddDefault("Default Auto", &m_defaultAuto);
		m_chooser.AddObject("My Auto", &m_myAuto);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		std::cout << "Starting SensorsTest ...\n";
	}

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to
	 * the
	 * chooser code above (like the commented example) or additional
	 * comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		std::string autoSelected = frc::SmartDashboard::GetString(
				"Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			m_autonomousCommand = &m_myAuto;
		} else {
			m_autonomousCommand = &m_defaultAuto;
		}

		m_autonomousCommand = m_chooser.GetSelected();

		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (m_autonomousCommand != nullptr) {
			m_autonomousCommand->Cancel();
			m_autonomousCommand = nullptr;
		}

		m_hcsr04 = new frc::Ultrasonic(0, 1, frc::Ultrasonic::kMilliMeters);
		m_hcsr04->SetAutomaticMode(true);
		count = 0;

		m_tinyLidar = new frc::I2C (frc::I2C::kOnboard, 0x10);
		m_lidarLite = new frc::I2C(frc::I2C::kOnboard, 0x62);
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		{
			std::cout << "#" << count++
					  << " | U = " << m_hcsr04->GetRangeInches()
//					  << " | TL = " << getTinyLidarDistance()
					  << " | LL = " << getLidarLiteDistance()
					  << std::endl;
		}
	}

	void TestPeriodic() override {}

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* m_autonomousCommand = nullptr;
	ExampleCommand m_defaultAuto;
	MyAutoCommand m_myAuto;
	frc::SendableChooser<frc::Command*> m_chooser;
	frc::Ultrasonic * m_hcsr04;
	frc::I2C * m_tinyLidar;
	frc::I2C * m_lidarLite;
	int count;

	int getTinyLidarDistance()
	{
		uint8_t command = 'D';
		uint8_t data [2];
		uint16_t distance;

		m_tinyLidar->Transaction(&command, 1, data, 2);
		distance = (((uint16_t)data[0]) << 8) | data[1];

		return distance;
	}

	int getLidarLiteDistance()
	{
		uint8_t status;
		uint8_t data[2];
		int tries = 500;
		uint16_t distanceInCm;

		// Initiate measurement
		m_lidarLite->Write(0x00, 0x04);

		// Wait for measurement to complete
		do {
			m_lidarLite->Read(0x01, 1, &status);
		} while((status & 0x01) && (--tries > 0));

		// Get 16-bit measurement as two 8-bit bytes. MSB in first byte
		m_lidarLite->Read(0x8f, 2, data);
		distanceInCm = ((uint16_t)data[0] << 8) | data[1];

		// Convert cm to mm
		return distanceInCm * 10.0;
	}
};

START_ROBOT_CLASS(Robot)
