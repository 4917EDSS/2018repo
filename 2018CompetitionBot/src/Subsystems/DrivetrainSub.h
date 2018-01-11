#ifndef DrivetrainSub_H
#define DrivetrainSub_H

#include <Commands/Subsystem.h>

class DrivetrainSub : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

  std::shared_ptr<TalonSRX> leftMotor1;
  std::shared_ptr<TalonSRX> leftMotor2;
  std::shared_ptr<TalonSRX> leftMotor3;
  std::shared_ptr<TalonSRX> rightMotor1;
  std::shared_ptr<TalonSRX> rightMotor2;
  std::shared_ptr<TalonSRX> rightMotor3;
 





public:

  DrivetrainSub();
	
 void InitDefaultCommand();
 void drive( double lSpeed, double rSpeed );
 






};

#endif  // DrivetrainSub_H
