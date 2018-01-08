#ifndef OI_H
#define OI_H

#include <WPILib.h>
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

// Joystick Ports
constexpr int DRIVER_CONTROLLER_PORT = 0;

// Joystick Axis
constexpr int DRIVER_LEFT_TANK_DRIVE_AXIS = 1;
constexpr int DRIVER_RIGHT_TANK_DRIVE_AXIS = 3;


class OI {
private:
	std::shared_ptr<frc::Joystick> driverController;

public:
	std::shared_ptr<frc::Joystick> getDriverController();
	OI();
};

#endif  // OI_H
