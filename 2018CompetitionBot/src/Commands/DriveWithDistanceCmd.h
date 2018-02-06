#ifndef DriveToVisionCmd_H
#define DriveToVisionCmd_H

#include "../CommandBase.h"

class DriveToVisionCmd : public CommandBase {
public:
	DriveToVisionCmd(int distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int targetDistance;
};

#endif  // DriveToVisionCmd_H
