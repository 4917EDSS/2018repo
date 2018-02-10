#ifndef DriveStraightCmd_H
#define DriveStraightCmd_H

#include "../CommandBase.h"

class DriveStraightCmd : public CommandBase {
public:
	DriveStraightCmd(int distance, float currentAngle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int targetDistance;
	float targetSpeed;
	float lastMoveTime;
	float targetAngle;
};

#endif  // DriveStraightCmd_H
