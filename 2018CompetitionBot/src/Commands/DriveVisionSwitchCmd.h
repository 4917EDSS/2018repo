#ifndef DriveVisionSwitchCmd_H
#define DriveVisionSwitchCmd_H

#include "../CommandBase.h"

class DriveVisionSwitchCmd : public CommandBase {
public:
	DriveVisionSwitchCmd(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double targetDistance;
	double lastMoveTime;
};

#endif  // DriveVisionSwitchCmd_H
