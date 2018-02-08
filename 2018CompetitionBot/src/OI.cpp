#include <Commands/ZeroAndIntakeGrp.h>
#include <Commands/SetHighGearHeldCmd.h>
#include "OI.h"
#include <Commands/RaiseRampCmd.h>
#include <WPILib.h>
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/DropBoxCmd.h"
#include <Commands/MoveElevatorToHeightCmd.h>
#include "Commands/KillEverythingCmd.h"

OI::OI() {
	// Process operator interface input here.
	driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
	driverController->SetXChannel(0);
	driverController->SetYChannel(1);
	driverController->SetZChannel(2);
	driverController->SetThrottleChannel(3);


	highGearBtn.reset(new JoystickButton(driverController.get(), HIGH_GEAR_BTN));
	highGearBtn->WhileHeld(new SetHighGearHeldCmd());
	killEverythingD1.reset(new frc::JoystickButton(driverController.get(), KILL_EVERYTHING_BTN_1));
	killEverythingD1->WhenPressed(new KillEverythingCmd());
	killEverythingD2.reset(new frc::JoystickButton(driverController.get(), KILL_EVERYTHING_BTN_2));
	killEverythingD2->WhenPressed(new KillEverythingCmd());

	operatorController.reset(new frc::Joystick(OPERATOR_CONTROLLER_PORT));
	operatorController->SetXChannel(0);
	operatorController->SetYChannel(1);
	operatorController->SetZChannel(2);
	operatorController->SetThrottleChannel(3);

	intakeBtn.reset(new frc::JoystickButton(operatorController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new ZeroAndIntakeGrp());
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
	dropBox.reset(new frc::JoystickButton(operatorController.get(), DROP_BOX_BTN));
	dropBox->WhenPressed(new DropBoxCmd());
	killEverythingO1.reset(new frc::JoystickButton(operatorController.get(), KILL_EVERYTHING_BTN_1));
	killEverythingO1->WhenPressed(new KillEverythingCmd());
	killEverythingO2.reset(new frc::JoystickButton(operatorController.get(), KILL_EVERYTHING_BTN_2));
	killEverythingO2->WhenPressed(new KillEverythingCmd());


}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
std::shared_ptr<frc::Joystick> OI::getOperatorController() {
	return operatorController;
}

