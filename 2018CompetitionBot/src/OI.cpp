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
	intakeBtn.reset(new frc::JoystickButton(driverController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new IntakeBoxCmd());
	reverseIntakeBtn.reset(new frc::JoystickButton(driverController.get(), REVERSE_INTAKE_BTN));
	reverseIntakeBtn->WhileHeld(new ReverseIntakeCmd());

	compressorsBtn.reset(new JoystickButton(driverController.get(), COMPRESSOR_BTN));
	compressorsBtn->WhileHeld(new OpenCompressorsHeldCmd());
}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
