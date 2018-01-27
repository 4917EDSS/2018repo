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
const int OPERATOR_CONTROLLER_PORT = 1;
const int INTAKE_BTN = 2;
constexpr int REVERSE_INTAKE_BTN = 3;
constexpr int HIGH_GEAR_BTN = 8;
const int PLACE_BOX_BTN = 2;
const int FLAPS_BTN = 4;
const int PLACE_BOX_HIGH_SCALE = 6;
const int PLACE_BOX_MEDIUM_SCALE = 8;
const int PLACE_BOX_LOW_SCALE = 5;
const int PLACE_BOX_SWITCH_BTN = 7;
const int MOVE_BOX_IN_OUT = 1;
const int ROTATE_BOX_BTN =0;

class OI {
public:
	OI();

	std::shared_ptr<frc::Joystick> getDriverController();
	std::shared_ptr<frc::Joystick> getOperatorController();
private:
	std::shared_ptr<frc::Joystick> driverController;
	std::shared_ptr<frc::Joystick> operatorController;
	std::shared_ptr<frc::JoystickButton> intakeBtn;
	std::shared_ptr<frc::JoystickButton> reverseIntakeBtn;
	std::shared_ptr<frc::JoystickButton> highGearBtn;
    std::shared_ptr<frc::JoystickButton> placeBoxBtn;
    std::shared_ptr<frc::JoystickButton> flapsBtn;
    std::shared_ptr<frc::JoystickButton> placeBoxHighScale;
    std::shared_ptr<frc::JoystickButton> placeBoxMediumScale;
    std::shared_ptr<frc::JoystickButton> placeBoxLowScale;
    std::shared_ptr<frc::JoystickButton> placeBoxSwitchBtn;
    std::shared_ptr<frc::JoystickButton> moveBoxInOut;
    std::shared_ptr<frc::JoystickButton> rotateBoxBtn;
    std::shared_ptr<frc::JoystickButton> elevatorUp;
    std::shared_ptr<frc::JoystickButton> elevatorDown;





};

#endif  // OI_H
