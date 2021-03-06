#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;
constexpr int LEFT_MOTOR1_CANID = 4;
constexpr int LEFT_MOTOR2_CANID = 5;
constexpr int LEFT_MOTOR3_CANID = 6;
constexpr int RIGHT_MOTOR1_CANID = 1;
constexpr int RIGHT_MOTOR2_CANID = 2;
constexpr int RIGHT_MOTOR3_CANID = 3;


// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;
constexpr int LEFT_MOTOR_ENC1_DIO = 0;
constexpr int LEFT_MOTOR_ENC2_DIO = 1;
constexpr int RIGHT_MOTOR_ENC1_DIO = 2;
constexpr int RIGHT_MOTOR_ENC2_DIO = 3;

// Pneumatic control module outputs
constexpr int SHIFTER_PCM_ID1 = 0;
constexpr int SHIFTER_PCM_ID2 = 1;

#endif  // ROBOTMAP_H
