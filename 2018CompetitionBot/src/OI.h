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

constexpr int DRIVER_CONTROLLER_PORT = 0;
constexpr int OPERATOR_CONTROLLER_PORT = 1;

// Driver
constexpr int HIGH_GEAR_BTN = 8;

// Operator
constexpr int ROTATE_BOX_BTN = 0;
constexpr int MOVE_BOX_IN_OUT = 1;
constexpr int INTAKE_BTN = 2;
constexpr int REVERSE_INTAKE_BTN = 3;
constexpr int DROP_BOX_BTN = 4;
constexpr int PLACE_BOX_LOW_SCALE_BTN = 5;
constexpr int PLACE_BOX_HIGH_SCALE_BTN = 6;
constexpr int PLACE_BOX_SWITCH_BTN = 7;
constexpr int PLACE_BOX_MEDIUM_SCALE_BTN = 8;
constexpr int FLAPS_BTN = 9;
constexpr int HOLD_BOX_BTN = 10;
constexpr int KILL_EVERYTHING_BTN_1 = 11;
constexpr int KILL_EVERYTHING_BTN_2 = 12;

constexpr int OPERATOR_ELEVATOR_AXIS = 3;

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
    std::shared_ptr<frc::JoystickButton> dropBox;
    std::shared_ptr<frc::JoystickButton> holdBox;
    std::shared_ptr<frc::JoystickButton> rotateBoxBtn;
    std::shared_ptr<frc::JoystickButton> elevatorUp;
    std::shared_ptr<frc::JoystickButton> elevatorDown;
    std::shared_ptr<frc::JoystickButton> killEverythingD1;
    std::shared_ptr<frc::JoystickButton> killEverythingD2;
    std::shared_ptr<frc::JoystickButton> killEverythingO1;
    std::shared_ptr<frc::JoystickButton> killEverythingO2;





};

#endif  // OI_H
