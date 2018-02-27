#ifndef DriveTurnWallCmd_H
#define DriveTurnCmd_H

#include "../CommandBase.h"

class DriveTurnWallCmd : public CommandBase {
public:
	DriveTurnWallCmd(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double turnDegrees;
	float lastMoveTime;
	int targetDistance;
};

#endif  // DriveTurnWallCmd_H

