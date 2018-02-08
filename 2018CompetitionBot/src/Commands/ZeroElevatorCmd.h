#ifndef ZeroElevatorCmd_H
#define ZeroElevatorCmd_H

#include "../CommandBase.h"

class ZeroElevatorCmd : public CommandBase {
public:
	ZeroElevatorCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ZeroElevatorCmd_H
