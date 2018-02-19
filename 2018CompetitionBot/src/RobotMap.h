#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/*
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

// Compressor Enabled
constexpr bool shiftersEnabled = true;

//CAN IDs
constexpr int LEFT1_DRIVE_MOTOR_CANID = 5;
constexpr int LEFT2_DRIVE_MOTOR_CANID = 7;
constexpr int LEFT3_DRIVE_MOTOR_CANID = 9;
constexpr int RIGHT1_DRIVE_MOTOR_CANID = 6;
constexpr int RIGHT2_DRIVE_MOTOR_CANID = 8;
constexpr int RIGHT3_DRIVE_MOTOR_CANID = 10;
constexpr int INTAKE_MOTOR_LEFT_CANID = 2;
constexpr int INTAKE_MOTOR_RIGHT_CANID = 4;
constexpr int ELEVATOR_MOTOR1_CANID = 1;
constexpr int ELEVATOR_MOTOR2_CANID = 3;

//DIOs
constexpr int LEFT_MOTOR_ENC1_DIO = 0;
constexpr int LEFT_MOTOR_ENC2_DIO = 1;
constexpr int RIGHT_MOTOR_ENC1_DIO = 2;
constexpr int RIGHT_MOTOR_ENC2_DIO = 3;
constexpr int ELEVATOR_MOTOR_ENC1_DIO = 4;
constexpr int ELEVATOR_MOTOR_ENC2_DIO = 5;
constexpr int INTAKE_LIMIT_SWITCH_DIO = 6;
constexpr int DRIVE_TRAIN_ULTRASONIC_TRIG_DIO = 7;
constexpr int DRIVE_TRAIN_ULTRASONIC_ECHO_DIO = 8;
constexpr int ELEVATOR_LOWER_LIMIT_DIO = 9;
constexpr int ELEVATOR_UPPER_LIMIT_DIO = 10;
constexpr int ELEVATOR_LIDAR_TRIG_DIO = 13;
constexpr int ELEVATOR_LIDAR_ECHO_DIO = 14;

//AIs
constexpr int INTAKE_DISTANCE_AI = 0;

//Drive Tolerances
const float DRIVE_BALANCE_TOLERANCE = 0.5;
const float DRIVE_DISTANCE_TOLERANCE = 15.0;
const float DISTANCE_SPEED_TOLERANCE = 10.0;
const float ELEVATOR_POSITION_TOLERANCE = 15.0;
const float DRIVE_TURN_TOLERANCE = 0.5;
const float DRIVE_RATE_TOLERANCE = 1;

// Pneumatic control module outputs
constexpr int SHIFTERS_PCM_ID = 1;
constexpr int JAWS_OPEN_PCM_ID = 2;
constexpr int JAWS_CLOSE_PCM_ID = 3;

// Ultrasonic distances
constexpr double ULTRASONIC_BOX_DISTANCE = 50.0;

/* Limelight Values
 * Vision Cam:
 * Exposure: 2
 * Red Balance: 1456
 * Blue Balance: 1472
 * Hue: 55 - 72
 * Saturation: 152 - 255
 * Value: 216 - 255
 * Drive Cam:
 * Light must be off
 * Exposure: 90
 * Red Balance: 1361
 * Blue Balance: 2500
 * Hue: 19 - 26
 * Saturation: 249 - 255
 * Value: 165 - 255
 *
 *
 *
 *
 */

#define AHRSInterface	frc::SPI::kMXP


#endif  // ROBOTMAP_H
