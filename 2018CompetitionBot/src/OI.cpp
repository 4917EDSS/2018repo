#include <Commands/IntakeBoxCmd.h>
#include "OI.h"

#include <WPILib.h>
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/OpenCompressorsHeldCmd.h"

OI::OI() {
	// Process operator interface input here.
	driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
	driverController->SetXChannel(0);
	driverController->SetYChannel(1);
	driverController->SetZChannel(2);
	driverController->SetThrottleChannel(3);
	intakeBtn.reset(new frc::JoystickButton(driverController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new IntakeBoxCmd());
	reverseIntakeBtn.reset(new frc::JoystickButton(driverController.get(), REVERSE_INTAKE_BTN));
	reverseIntakeBtn->WhileHeld(new ReverseIntakeCmd());

	highGearBtn.reset(new JoystickButton(driverController.get(), HIGH_GEAR_BTN));
	highGearBtn->WhileHeld(new OpenCompressorsHeldCmd());
}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
