#ifndef OI_H
#define OI_H

#include "WPILib.h"

const int DRIVER_CONTROLLER_PORT = 0;

class OI {
public:
	OI();

	std::shared_ptr<frc::Joystick> getDriverController();

private:
	std::shared_ptr<frc::Joystick> driverController;
};

#endif  // OI_H
