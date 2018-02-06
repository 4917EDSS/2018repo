#ifndef DriveVisionBoxCmd_H
#define DriveVisionBoxCmd_H

#include "../CommandBase.h"

class DriveVisionBoxCmd : public CommandBase {
public:
	DriveVisionBoxCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveVisionBoxCmd_H
