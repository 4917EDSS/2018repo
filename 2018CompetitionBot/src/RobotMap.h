#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/*
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

//CAN IDs
constexpr int DRIVE_MOTOR_LEFT1_CANID = 5;
constexpr int DRIVE_MOTOR_LEFT2_CANID = 7;
constexpr int DRIVE_MOTOR_LEFT3_CANID = 9;
constexpr int DRIVE_MOTOR_RIGHT1_CANID = 6;
constexpr int DRIVE_MOTOR_RIGHT2_CANID = 8;
constexpr int DRIVE_MOTOR_RIGHT3_CANID = 10;
constexpr int INTAKE_MOTOR_LEFT_CANID = 2;
constexpr int INTAKE_MOTOR_RIGHT_CANID = 4;
constexpr int ARM_FOLDER_CANID = 11;
constexpr int ELEVATOR_MOTOR1_CANID = 1;
constexpr int ELEVATOR_MOTOR2_CANID = 3;

//DIOs (0..9 are on RoboRio, 10..19 are on MXP expansion port)
constexpr int DRIVE_MOTOR_LEFT_ENC1_DIO = 0;
constexpr int DRIVE_MOTOR_LEFT_ENC2_DIO = 1;
constexpr int DRIVE_MOTOR_RIGHT_ENC1_DIO = 2;
constexpr int DRIVE_MOTOR_RIGHT_ENC2_DIO = 3;
constexpr int ELEVATOR_MOTOR_ENC1_DIO = 4;
constexpr int ELEVATOR_MOTOR_ENC2_DIO = 5;
constexpr int INTAKE_LIMIT_CLOSE_DIO = 6;
constexpr int INTAKE_LIMIT_FAR_DIO = 7;
// constexpr int FREE_DIO = 8;
constexpr int ELEVATOR_LOWER_LIMIT_DIO = 9;
constexpr int ELEVATOR_LIDAR_TRIG_DIO = 10;
constexpr int ELEVATOR_LIDAR_ECHO_DIO = 11;
constexpr int DRIVETRAIN_FRONT_ULTRASONIC_TRIG_DIO = 12;
constexpr int DRIVETRAIN_FRONT_ULTRASONIC_ECHO_DIO = 13;

//AIs
constexpr int INTAKE_DISTANCE_AI = 0;
constexpr int DRIVETRAIN_REAR_ULTRASONIC_AI = 1;

// Pneumatic control module outputs
constexpr int SHIFTERS_PCM_ID = 1;
constexpr int JAWS_OPEN_PCM_ID = 2;
constexpr int JAWS_CLOSE_PCM_ID = 3;

// AHRS (i.e. navX) interface
#define AHRSInterface	frc::SPI::kMXP


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

#endif  // ROBOTMAP_H
