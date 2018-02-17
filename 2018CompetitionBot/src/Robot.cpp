#include <memory>
#include <iostream>
#include <string>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <CommandBase.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Components/LidarLite.h>
#include <Components/AutoDecider/AutoDecider.h>
#include <Components/AutoDecider/AutoScaleBackupSwitchLeft.h>
#include <Components/AutoDecider/AutoScaleBackupSwitchRight.h>
#include <Components/AutoDecider/AutoScaleLeft.h>
#include <Components/AutoDecider/AutoScaleRight.h>
#include <Components/AutoDecider/AutoSwitch.h>
#include <Components/Logging/Log.h>
#include <Components/LinearInterpolation.h>
#include <Commands/DriveTurnCmd.h>
#include <Commands/DriveStraightCmd.h>
#include <Commands/ResetEncodersCmd.h>
#include <Commands/AutoScaleLeftToRightGrp.h>
#include <Commands/DriveUntilDistanceCmd.h>
#include <Commands/IntakeUntilLimitCmd.h>
#include <Commands/SetHighGearHeldCmd.h>
#include <Subsystems/DrivetrainSub.h>

class Robot: public frc::IterativeRobot {
public:

	void RobotInit() override {
		// chooser.AddObject("My Auto", new MyAutoCommand());
		SetSmartDashboardDriverContent();
		SetSmartDashboardAutoOptions();
		logger.enableChannels(logger.WARNINGS | logger.ERRORS | logger.ASSERTS | logger.DRIVETRAIN);
		logger.enableChannels( logger.DEBUG);	// Should look at these during development
		logger.addOutputPath(new frc4917::ConsoleOutput());						// Enable console output and/or
//		logger.addOutputPath(new frc4917::SyslogOutput("10.49.17.20"));			// Enable syslog output
		logger.send(logger.DEBUG, "Robot code started @ %f\n", GetTime());
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		CommandBase::drivetrainSub->setLowGear();
		CommandBase::drivetrainSub->resetAHRS();
		CommandBase::drivetrainSub->resetEncoders();
		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		std::shared_ptr<frc4917::AutoDecider> autoDecider = chooser->GetSelected().lock();
		autoDecider->setGameData(gameData);
		autonomousCommand.reset(autoDecider->getCommand());

		if (autonomousCommand != nullptr) {
			autonomousCommand->Start();
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
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		UpdateSmartDashboard();
		//std::cout<<lidarLite->getDistance()<<std::endl;
	}

	void TestPeriodic() override {

	}
	void UpdateSmartDashboard(){
		SmartDashboard::PutNumber("Left Drive Motor Enc", CommandBase::drivetrainSub->getLeftEncoder());
		SmartDashboard::PutNumber("Right Drive Motor Enc", CommandBase::drivetrainSub->getRightEncoder());
		SmartDashboard::PutNumber("Right Encoder Speed", CommandBase::drivetrainSub->getRightEncoderSpeed());
		SmartDashboard::PutNumber("Left Encoder Speed", CommandBase::drivetrainSub->getLeftEncoderSpeed());
		SmartDashboard::PutNumber("Elevator Down", CommandBase::elevatorSub->isElevatorDown());
		SmartDashboard::PutNumber("Elevator Encoder", CommandBase::elevatorSub->getElevatorEncoder());
		SmartDashboard::PutNumber("Current Angle", CommandBase::drivetrainSub->getAngle());
		SmartDashboard::PutBoolean("Is box in?", CommandBase::intakeSub->isBoxIn());
	}


	void SetSmartDashboardDriverContent(){
		SmartDashboard::PutData("2m Drive straight", new DriveStraightCmd(2000,0.0));
		SmartDashboard::PutData("300mm Drive straight", new DriveStraightCmd(300,0.0));
		SmartDashboard::PutData("Drive Turn 45", new DriveTurnCmd(45));
		SmartDashboard::PutData("Drive Turn 10", new DriveTurnCmd(10));
		SmartDashboard::PutData("Drive Turn 90", new DriveTurnCmd(90));
		SmartDashboard::PutData("7.5m Drive Straight", new DriveStraightCmd(7500,0.0));
		SmartDashboard::PutData("Reset Encoders", new ResetEncodersCmd());
		SmartDashboard::PutData("Victory Lap Auto", new AutoScaleLeftToRightGrp());
		SmartDashboard::PutData("Drive until 100 mm", new DriveUntilDistanceCmd(100));
	}

private:
	std::shared_ptr<frc::Command> autonomousCommand;
	std::unique_ptr<frc::SendableChooser<std::shared_ptr<frc4917::AutoDecider>> > chooser;


	void SetSmartDashboardAutoOptions() {
		chooser.reset(new frc::SendableChooser<std::shared_ptr<frc4917::AutoDecider>>());
		//ALL AUTO NAMES MUST BE EQUAL TO OR LESS THAN 15 CHARACTERS LONG
		chooser->AddDefault("L Scale switch", std::shared_ptr<frc4917::AutoDecider>(new frc4917::AutoScaleBackupSwitchLeft()));
		chooser->AddObject("R Scale Switch", std::shared_ptr<frc4917::AutoDecider>(new frc4917::AutoScaleBackupSwitchRight()));
		chooser->AddObject("L Scale", std::shared_ptr<frc4917::AutoDecider>(new frc4917::AutoScaleLeft()));
		chooser->AddObject("R Scale", std::shared_ptr<frc4917::AutoDecider>(new frc4917::AutoScaleRight()));
		chooser->AddObject("M Switch", std::shared_ptr<frc4917::AutoDecider>(new frc4917::AutoSwitch()));

		SmartDashboard::PutData("Auto Mode", chooser.get());
	}
};







START_ROBOT_CLASS(Robot)
