#include <Commands/IntakeBoxCmd.h>
#include "OI.h"

#include <WPILib.h>
#include "Commands/ReverseIntakeCmd.h"

OI::OI() {
	// Process operator interface input here.
	driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
	driverController->SetXChannel(0);
	driverController->SetYChannel(1);
	intakeBtn.reset(new frc::JoystickButton(driverController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new IntakeBoxCmd());
	reverseIntakeBtn.reset(new frc::JoystickButton(driverController.get(), REVERSE_INTAKE_BTN));
	reverseIntakeBtn->WhileHeld(new ReverseIntakeCmd());
}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
