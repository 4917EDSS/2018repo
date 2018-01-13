#include "OI.h"

#include <WPILib.h>
#include "Commands/RunIntakeCmd.h"
#include "Commands/ReverseIntakeCmd.h"

OI::OI() {
	// Process operator interface input here.
	driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
	intakeBtn.reset(new frc::JoystickButton(driverController.get(), INTAKE_BTN));
	intakeBtn->WhileHeld(new RunIntakeCmd());
	reverseIntakeBtn.reset(new frc::JoystickButton(driverController.get(), REVERSE_INTAKE_BTN));
	reverseIntakeBtn->WhileHeld(new ReverseIntakeCmd());
}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
