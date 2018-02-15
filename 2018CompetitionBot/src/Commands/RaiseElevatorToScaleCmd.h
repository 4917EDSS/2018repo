#ifndef RaiseElevatorToScaleCmd_H
#define RaiseElevatorToScaleCmd_H

#include "../CommandBase.h"

class RaiseElevatorToScaleCmd : public CommandBase {
public:
	RaiseElevatorToScaleCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RaiseElevatorToScaleCmd_H
