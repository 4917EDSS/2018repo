#include <Commands/IntakeUntilDistanceCmd.h>
#include <Commands/SetHighGearHeldCmd.h>
#include "OI.h"
#include <Commands/RaiseRampCmd.h>
#include <WPILib.h>
#include "Commands/ReverseIntakeCmd.h"
#include <Commands/MoveElevatorToHeightCmd.h>

OI::OI() {
	// Process operator interface input here.
	driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
	driverController->SetXChannel(0);
	driverController->SetYChannel(1);
	driverController->SetZChannel(2);
	driverController->SetThrottleChannel(3);


	highGearBtn.reset(new JoystickButton(driverController.get(), HIGH_GEAR_BTN));
	highGearBtn->WhileHeld(new SetHighGearHeldCmd());

	operatorController.reset(new frc::Joystick(OPERATOR_CONTROLLER_PORT));
	operatorController->SetXChannel(0);
	operatorController->SetYChannel(1);
	operatorController->SetZChannel(2);
	operatorController->SetThrottleChannel(3);

	intakeBtn.reset(new frc::JoystickButton(operatorController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new IntakeUntilDistanceCmd(ULTRASONIC_BOX_DISTANCE));
	flapsBtn.reset(new frc::JoystickButton(operatorController.get(), FLAPS_BTN));
	flapsBtn ->WhenPressed(new RaiseRampCmd());
	placeBoxHighScale.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_HIGH_SCALE));
	placeBoxHighScale ->WhenPressed(new MoveElevatorToHeightCmd(7));
	placeBoxMediumScale.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_MEDIUM_SCALE));
	placeBoxMediumScale ->WhenPressed(new MoveElevatorToHeightCmd(5));
	placeBoxLowScale.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_LOW_SCALE));
	placeBoxLowScale ->WhenPressed(new MoveElevatorToHeightCmd(3));
	placeBoxSwitchBtn.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_SWITCH_BTN));
	placeBoxSwitchBtn ->WhenPressed(new MoveElevatorToHeightCmd(4));
	reverseIntakeBtn.reset(new frc::JoystickButton(operatorController.get(), REVERSE_INTAKE_BTN));
	reverseIntakeBtn->WhileHeld(new ReverseIntakeCmd());




}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
std::shared_ptr<frc::Joystick> OI::getOperatorController() {
	return operatorController;
}

