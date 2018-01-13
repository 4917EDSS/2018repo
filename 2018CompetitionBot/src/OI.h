#ifndef OI_H
#define OI_H

#include "WPILib.h"

const int DRIVER_CONTROLLER_PORT = 0;
const int INTAKE_BTN = 2;

class OI {
public:
	OI();

	std::shared_ptr<frc::Joystick> getDriverController();

private:
	std::shared_ptr<frc::Joystick> driverController;
	std::shared_ptr<frc::JoystickButton>intakeBtn;
};

#endif  // OI_H
