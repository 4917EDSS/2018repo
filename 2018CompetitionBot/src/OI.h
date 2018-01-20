#ifndef OI_H
#define OI_H

#include "WPILib.h"

/*
 * ON LOGITECH CONTROLLER:
 * X = 1
 * A = 2
 * B = 3
 * Y = 4
 * LB = 5
 * RB = 6
 * LT = 7
 * RT = 8
 * Select = 9
 * Start = 10
 * L3 = 11
 * R3 = 12
 * Left Vertical = 1
 * Left Horizontal = 0
 * Right Vertical = 3
 * Right Horizontal = 2
 *
 */

const int DRIVER_CONTROLLER_PORT = 0;
const int INTAKE_BTN = 2;
constexpr int REVERSE_INTAKE_BTN = 3;
constexpr int HIGH_GEAR_BTN = 8;

class OI {
public:
	OI();

	std::shared_ptr<frc::Joystick> getDriverController();

private:
	std::shared_ptr<frc::Joystick> driverController;
	std::shared_ptr<frc::JoystickButton> intakeBtn;
	std::shared_ptr<frc::JoystickButton> reverseIntakeBtn;
	std::shared_ptr<frc::JoystickButton> highGearBtn;
};

#endif  // OI_H
