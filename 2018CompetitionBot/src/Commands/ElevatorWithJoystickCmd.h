#ifndef ElevatorWithJoystickCmd_H
#define ElevatorWithJoystickCmd_H

#include "../CommandBase.h"

class ElevatorWithJoystickCmd : public CommandBase {
public:
	ElevatorWithJoystickCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorWithJoystickCmd_H
