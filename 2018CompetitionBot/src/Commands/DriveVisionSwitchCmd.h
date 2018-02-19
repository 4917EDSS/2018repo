#ifndef DriveVisionSwitchCmd_H
#define DriveVisionSwitchCmd_H

#include "../CommandBase.h"

class DriveVisionSwitchCmd : public CommandBase {
public:
	DriveVisionSwitchCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveVisionSwitchCmd_H
