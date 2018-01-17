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

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

// Compressor Enabled
constexpr bool compressorsEnabled = true;

//CAN IDs
constexpr int LEFT1_DRIVE_MOTOR_CANID = 1;
constexpr int LEFT2_DRIVE_MOTOR_CANID = 3;
constexpr int LEFT3_DRIVE_MOTOR_CANID = 5; 
constexpr int RIGHT1_DRIVE_MOTOR_CANID = 2;
constexpr int RIGHT2_DRIVE_MOTOR_CANID = 4;
constexpr int RIGHT3_DRIVE_MOTOR_CANID = 6;
constexpr int INTAKE_MOTOR_CANID = 7;
constexpr int ELEVATOR_MOTOR_CANID = 8;

//DIOs
constexpr int LEFT_MOTOR_ENC1_DIO = 0;
constexpr int LEFT_MOTOR_ENC2_DIO = 1;
constexpr int RIGHT_MOTOR_ENC1_DIO = 2;
constexpr int RIGHT_MOTOR_ENC2_DIO = 3;
constexpr int ELEVATOR_MOTOR_ENC1_DIO = 4;
constexpr int ELEVATOR_MOTOR_ENC2_DIO = 5;
constexpr int INTAKE_LIMIT_SWITCH = 6;

//Drive Tolerances
const float DRIVE_BALANCE_TOLERANCE = 1.0;
const float DRIVE_DISTANCE_TOLERANCE = 1.0;
const float DISTANCE_SPEED_TOLERANCE = 40.0;
const float ELEVATOR_POSITION_TOLERANCE = 40.0;
const float DRIVE_TURN_TOLERANCE = 0.5;
const float DRIVE_RATE_TOLERANCE = 1;

// Pneumatic control module outputs
constexpr int COMPRESSORS_PCM_ID1 = 1;
constexpr int COMPRESSORS_PCM_ID2 = 2;

#define AHRSInterface	frc::SPI::kMXP


#endif  // ROBOTMAP_H
