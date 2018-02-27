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
#include <Components/Logging/Log.h>
#include <Components/LinearInterpolation.h>
#include <Commands/DriveTurnCmd.h>
#include <Commands/DriveStraightCmd.h>
#include <Commands/ResetEncodersCmd.h>
#include <Commands/ResetAHRSCmd.h>
#include <Commands/AutoScaleLeftToRightGrp.h>
#include <Commands/DriveUntilDistanceCmd.h>
#include <Commands/IntakeUntilLimitCmd.h>
#include <Commands/SetHighGearHeldCmd.h>
#include <Commands/DriveVisionBoxCmd.h>
#include "Subsystems/DrivetrainSub.h"
#include <networktables/NetworkTableInstance.h>

#include <Commands/AutoSwitchLeftToLeftGrp.h>
#include<Commands/AutoSwitchRightToRightGrp.h>
#include<Commands/AutoScaleLeftToLeftGrp.h>
#include <Commands/AutoScaleRightToRightGrp.h>
#include <Commands/AutoSwitchCenterToRightGrp.h>
#include <Commands/AutoSwitchCenterToLeftGrp.h>
#include <Commands/AutoScaleRightToLeftGrp.h>
#include <Commands/AutoScaleLeftToRightGrp.h>
#include <Commands/AutoSwitchRightToLeftGrp.h>
#include <Commands/AutoSwitchLeftToRightGrp.h>
#include <Commands/DriveVisionSwitchCmd.h>
#include <Commands/SilkyMotionCmd.h>
#include <Components/Logging/GlobalLogging.h>


class Robot: public frc::IterativeRobot {
public:

	void RobotInit() override {
		// chooser.AddObject("My Auto", new MyAutoCommand());
		SetSmartDashboardDriverContent();
		SetSmartDashboardAutoOptions();

		// Setup logging system
		std::string syslogTargetAddress = (Preferences::GetInstance())->GetString("SyslogTargetAddress", "10.49.17.100");
		logger.enableChannels(logger.WARNINGS | logger.ERRORS | logger.ASSERTS);	// These should stay on during competition
		logger.enableChannels(logger.DEBUG | logger.DRIVETRAIN | logger.PERIODIC );	// Should look at these during development
		//logger.addOutputPath(new frc4917::ConsoleOutput());						// Enable console output and/or
		logger.addOutputPath(new frc4917::SyslogOutput(syslogTargetAddress));		// Enable syslog output
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
		CommandBase::intakeSub->setJawsClose();
		CommandBase::drivetrainSub->setLowGear();
		CommandBase::drivetrainSub->resetAHRS();
		CommandBase::drivetrainSub->resetEncoders();
		nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("pipeline").SetDouble(0.0);
		nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("ledMode").SetDouble(0.0);
		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		if(gameData[0] == 'R' && gameData[1] == 'R'){
			autonomousCommand = chooserRR->GetSelected().lock();
		}
		if(gameData[0] == 'L' && gameData[1] == 'R'){
			autonomousCommand = chooserLR->GetSelected().lock();
		}
		if(gameData[0] == 'L' && gameData[1] == 'L'){
			autonomousCommand = chooserLL->GetSelected().lock();
		}
		if(gameData[0] == 'R' && gameData[1] == 'L'){
			autonomousCommand = chooserRL->GetSelected().lock();
		}
		if (autonomousCommand != nullptr) {
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		globalLogging.logPeriodicValues();
		CommandBase::drivetrainSub->logPeriodicValues();
		CommandBase::elevatorSub->logPeriodicValues();
		//CommandBase::intakeSub->logPeriodicValues();  // TODO: Test
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
		nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("pipeline").SetDouble(1.0);
		nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("ledMode").SetDouble(1.0);
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		UpdateSmartDashboard();
		globalLogging.logPeriodicValues();
		CommandBase::drivetrainSub->logPeriodicValues();
		CommandBase::elevatorSub->logPeriodicValues();
		//CommandBase::intakeSub->logPeriodicValues();	// TODO: Test
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
		SmartDashboard::PutBoolean("Is box at jaws?", CommandBase::intakeSub->isBoxAtJaws());
		SmartDashboard::PutNumber("Intake Distance", CommandBase::intakeSub->getBoxDistance());
	}


	void SetSmartDashboardDriverContent(){
		SmartDashboard::PutData("2m Drive straight", new DriveStraightCmd(2000,0.0));
		SmartDashboard::PutData("300mm Drive straight", new DriveStraightCmd(300,0.0));
		SmartDashboard::PutData("Drive Turn 45", new DriveTurnCmd(45));
		SmartDashboard::PutData("Drive Turn 20", new DriveTurnCmd(20));
		SmartDashboard::PutData("Drive Turn -25", new DriveTurnCmd(-25));
		SmartDashboard::PutData("7.5m Drive Straight", new DriveStraightCmd(7500,0.0));
		SmartDashboard::PutData("Reset Encoders", new ResetEncodersCmd());
		SmartDashboard::PutData("Reset AHRS", new ResetAHRSCmd());
		SmartDashboard::PutData("Drive to vision", new DriveVisionBoxCmd());
		SmartDashboard::PutData("Drive to vision switch 1500mm", new DriveVisionSwitchCmd(1500));
		SmartDashboard::PutData("SilkyMotionCmd", new SilkyMotionCmd(std::vector<double> {3001, 2001, 3000, 2000}, std::vector<double> {0, -90, 0, 180}));
	}

private:
	std::shared_ptr<frc::Command> autonomousCommand;
	std::unique_ptr<frc::SendableChooser<std::shared_ptr<frc::Command>> > chooserRR;
	std::unique_ptr<frc::SendableChooser<std::shared_ptr<frc::Command>> > chooserLL;
	std::unique_ptr<frc::SendableChooser<std::shared_ptr<frc::Command>> > chooserRL;
	std::unique_ptr<frc::SendableChooser<std::shared_ptr<frc::Command>> > chooserLR;



	void SetSmartDashboardAutoOptions() {
		chooserRL.reset(new frc::SendableChooser<std::shared_ptr<frc::Command>>());
		chooserRR.reset(new frc::SendableChooser<std::shared_ptr<frc::Command>>());
		chooserLL.reset(new frc::SendableChooser<std::shared_ptr<frc::Command>>());
		chooserLR.reset(new frc::SendableChooser<std::shared_ptr<frc::Command>>());

		//ALL AUTO NAMES MUST BE EQUAL TO OR LESS THAN 15 CHARACTERS LONG
		chooserRR->AddDefault("L Switch", std::shared_ptr<frc::Command>(new AutoSwitchLeftToRightGrp()));
		chooserRR->AddObject("R Switch", std::shared_ptr<frc::Command>(new AutoSwitchRightToRightGrp()));
		chooserRR->AddObject("L Scale", std::shared_ptr<frc::Command>(new AutoScaleLeftToRightGrp()));
		chooserRR->AddObject("R Scale", std::shared_ptr<frc::Command>(new AutoScaleRightToRightGrp()));
		chooserRR->AddObject("C Switch", std::shared_ptr<frc::Command>(new AutoSwitchCenterToRightGrp()));

		chooserLR->AddDefault("L Switch", std::shared_ptr<frc::Command>(new AutoSwitchLeftToLeftGrp()));
		chooserLR->AddObject("R Switch", std::shared_ptr<frc::Command>(new AutoSwitchRightToLeftGrp()));
		chooserLR->AddObject("L Scale", std::shared_ptr<frc::Command>(new AutoScaleLeftToRightGrp()));
		chooserLR->AddObject("R Scale", std::shared_ptr<frc::Command>(new AutoScaleRightToRightGrp()));
		chooserLR->AddObject("C Switch", std::shared_ptr<frc::Command>(new AutoSwitchCenterToLeftGrp()));

		chooserLL->AddDefault("L Switch", std::shared_ptr<frc::Command>(new AutoSwitchLeftToLeftGrp()));
		chooserLL->AddObject("R Switch", std::shared_ptr<frc::Command>(new AutoSwitchRightToLeftGrp()));
		chooserLL->AddObject("L Scale", std::shared_ptr<frc::Command>(new AutoScaleLeftToLeftGrp()));
		chooserLL->AddObject("R Scale", std::shared_ptr<frc::Command>(new AutoScaleRightToLeftGrp()));
		chooserLL->AddObject("C Switch", std::shared_ptr<frc::Command>(new AutoSwitchCenterToLeftGrp()));

		chooserRL->AddDefault("L Switch", std::shared_ptr<frc::Command>(new AutoSwitchLeftToRightGrp()));
		chooserRL->AddObject("R Switch", std::shared_ptr<frc::Command>(new AutoSwitchRightToRightGrp()));
		chooserRL->AddObject("L Scale", std::shared_ptr<frc::Command>(new AutoScaleLeftToLeftGrp()));
		chooserRL->AddObject("R Scale", std::shared_ptr<frc::Command>(new AutoScaleRightToLeftGrp()));
		chooserRL->AddObject("C Switch", std::shared_ptr<frc::Command>(new AutoSwitchCenterToRightGrp()));

		SmartDashboard::PutData("Sw R Sc R", chooserRR.get());
		SmartDashboard::PutData("Sw R Sc L", chooserRL.get());
		SmartDashboard::PutData("Sw L Sc L", chooserLL.get());
		SmartDashboard::PutData("Sw L Sc R", chooserLR.get());
	}
};



START_ROBOT_CLASS(Robot)
