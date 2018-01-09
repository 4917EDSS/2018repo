#include <WPILib.h>
#include "DrivetrainSub.h"
#include "../RobotMap.h"
#include "../Commands/DriveWithJoystickCmd.h"

// Drivetrain values

constexpr float DRIVETRAIN_DIS_PER_PULSE_LEFT = 3000.0/1925.0;
constexpr float DRIVETRAIN_DIS_PER_PULSE_RIGHT = 3000.0/-1764.3939225673676;
constexpr int ENCODER_CONVERSION_FACTOR = 4;
constexpr double SHIFT_HIGH_SPEED = 5000.0;
constexpr double SHIFT_LOW_SPEED = 1000.0;


DrivetrainSub::DrivetrainSub() : Subsystem("DrivetrainSub") {
	highGear = false;
	shiftHighSpeed = SHIFT_HIGH_SPEED;
	shiftLowSpeed = SHIFT_LOW_SPEED;

}

void DrivetrainSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystickCmd());
}

void DrivetrainSub::initHardware() {
	leftMotor1.reset(new CANTalon(LEFT_MOTOR1_CANID));
	leftMotor2.reset(new CANTalon(LEFT_MOTOR2_CANID));
	leftMotor3.reset(new CANTalon(LEFT_MOTOR3_CANID));
	rightMotor1.reset(new CANTalon(RIGHT_MOTOR1_CANID));
	rightMotor2.reset(new CANTalon(RIGHT_MOTOR2_CANID));
	rightMotor3.reset(new CANTalon(RIGHT_MOTOR3_CANID));
	leftMotorEnc.reset(new frc::Encoder(LEFT_MOTOR_ENC1_DIO, LEFT_MOTOR_ENC2_DIO));
	rightMotorEnc.reset(new frc::Encoder(RIGHT_MOTOR_ENC1_DIO, RIGHT_MOTOR_ENC2_DIO));
	leftMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE_LEFT*ENCODER_CONVERSION_FACTOR);
	rightMotorEnc->SetDistancePerPulse(DRIVETRAIN_DIS_PER_PULSE_RIGHT*ENCODER_CONVERSION_FACTOR);
	shifter.reset(new frc::DoubleSolenoid(SHIFTER_PCM_ID1, SHIFTER_PCM_ID2));

	// Make these properly available in Test mode
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	lw->AddActuator("Drivetrain L", "Left Motor 1", leftMotor1);
	lw->AddActuator("Drivetrain L", "Left Motor 2", leftMotor2);
	lw->AddActuator("Drivetrain L", "Left Motor 3", leftMotor3);
	lw->AddSensor("Drivetrain L", "Encoder", leftMotorEnc);
	lw->AddActuator("Drivetrain R", "Right Motor 1", rightMotor1);
	lw->AddActuator("Drivetrain R", "Right Motor 2", rightMotor2);
	lw->AddActuator("Drivetrain R", "Right Motor 3", rightMotor3);
	lw->AddSensor("Drivetrain R", "Encoder", rightMotorEnc);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DrivetrainSub::drive(double lPower, double rPower)
{
#if 1
	frc::Preferences *prefs = Preferences::GetInstance();
	if( prefs )
	{
		shiftHighSpeed = prefs->GetDouble("HighGearShiftSpeed", SHIFT_HIGH_SPEED);
		shiftLowSpeed = prefs->GetDouble("LowGearShiftSpeed", SHIFT_LOW_SPEED);
	}
#endif

	// Speed is in mm/second
	double curSpeed = fabs(leftMotorEnc->GetRate());
	if( !highGear && (curSpeed > shiftHighSpeed) )
	{
		setShifter(SOLENOID_HIGH_GEAR);
		highGear = true;
	}
	else if( highGear && (curSpeed < shiftLowSpeed) )
	{
		setShifter(SOLENOID_LOW_GEAR);
		highGear = false;
	}

	leftMotor1->Set(-lPower);
	leftMotor2->Set(-lPower);
	leftMotor3->Set(-lPower);

	rightMotor1->Set(rPower);
	rightMotor2->Set(rPower);
	rightMotor3->Set(rPower);
}

void DrivetrainSub::setShifter(frc::DoubleSolenoid::Value shiftState)
{
	shifter->Set(shiftState);
}

bool DrivetrainSub::isInHighGear()
{
	return highGear;
}

double DrivetrainSub::getLeftEncoderRaw()
{
	return leftMotorEnc->GetRaw();
}

double DrivetrainSub::getRightEncoderRaw()
{
	return rightMotorEnc->GetRaw();
}

double DrivetrainSub::getLeftEncoder()
{
	return leftMotorEnc->Get();
}

double DrivetrainSub::getRightEncoder()
{
	return rightMotorEnc->Get();
}

double DrivetrainSub::getLeftEncoderSpeed()
{
	return leftMotorEnc->GetRate();
}

double DrivetrainSub::getRightEncoderSpeed()
{
	return rightMotorEnc->GetRate();
}

