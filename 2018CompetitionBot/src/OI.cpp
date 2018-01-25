#include <Commands/IntakeUntilDistanceCmd.h>
#include <Commands/SetHighGearHeldCmd.h>
#include "OI.h"

#include <WPILib.h>
#include "Commands/ReverseIntakeCmd.h"

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
	operatorController->
	intakeBtn.reset(new frc::JoystickButton(operatorController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new IntakeUntilDistanceCmd(ULTRASONIC_BOX_DISTANCE));
	reverseIntakeBtn.reset(new frc::JoystickButton(operatorController.get(), REVERSE_INTAKE_BTN));
	reverseIntakeBtn->WhileHeld(new ReverseIntakeCmd());



}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
