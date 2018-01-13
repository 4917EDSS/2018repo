#ifndef DriveStraightCmd_H
#define DriveStraightCmd_H

#include "../CommandBase.h"

class DriveStraightCmd : public CommandBase {
public:
	DriveStraightCmd(int distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int targetDistance;
	float targetSpeed;
	float timeFromLastMove;
	float lastMoveTime;
};

#endif  // DriveStraightCmd_H
