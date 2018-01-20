#include "ElevatorSub.h"
#include "../RobotMap.h"

constexpr float LIFT_P = 1;
constexpr float LIFT_I = 0;
constexpr float LIFT_D = 0;
const float LIFT_TOLERANCE = 1;

ElevatorSub::ElevatorSub() : Subsystem("ExampleSubsystem") {
	elevatorMotor.reset(new TalonSRX(ELEVATOR_MOTOR_CANID));
	elevatorMotorEnc.reset(new frc::Encoder(ELEVATOR_MOTOR_ENC1_DIO, ELEVATOR_MOTOR_ENC2_DIO));
	// NEED TO DO liftPID.reset(new PIDController(LIFT_P, LIFT_I, LIFT_D, elevatorMotorEnc.get(), elevatorMotor.get()));
	target = 0;
}

void ElevatorSub::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ElevatorSub::setElevatorMotor(float speed){
	elevatorMotor->Set(ControlMode::PercentOutput,-speed);
}

double ElevatorSub::getElevatorEncoder() {
	return elevatorMotorEnc->GetDistance();
}

void ElevatorSub::resetElevatorEncoder() {
	elevatorMotorEnc->Reset();
}

void ElevatorSub::setTarget(int newTarget) {
	target = newTarget;
}

void ElevatorSub::update(){
	double currentPosition = getElevatorEncoder();
	if (currentPosition < target - ELEVATOR_POSITION_TOLERANCE){
		setElevatorMotor(1.0);
	}
	else if (currentPosition > target + ELEVATOR_POSITION_TOLERANCE){
		setElevatorMotor(-1.0);
	}
	else{
		setElevatorMotor(0.0);
	}
}

void ElevatorSub::enableLiftPID(float setPoint){
	Preferences *prefs = Preferences::GetInstance();
	liftPID->SetPID(prefs->GetFloat("LiftP", LIFT_P), prefs->GetFloat("LiftI", LIFT_I), prefs->GetFloat("LiftD", LIFT_D));
	liftPID->SetAbsoluteTolerance(prefs->GetFloat("LiftTolerance", LIFT_TOLERANCE));
	liftPID->SetSetpoint(setPoint);
	liftPID->Enable();
}

void ElevatorSub::disableLiftPID(){
	liftPID->Disable();
}

bool ElevatorSub::PIDLiftIsFinished(){
	return liftPID->OnTarget();
}
