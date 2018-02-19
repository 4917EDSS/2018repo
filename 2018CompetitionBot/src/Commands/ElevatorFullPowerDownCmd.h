#ifndef ElevatorFullPowerDownCmd_H
#define ElevatorFullPowerDownCmd_H

#include "../CommandBase.h"

class ElevatorFullPowerDownCmd : public CommandBase {
public:
	ElevatorFullPowerDownCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorFullPowerDownCmd_H
