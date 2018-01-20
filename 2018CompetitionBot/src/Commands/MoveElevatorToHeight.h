#ifndef MoveElevatorToHeight_H
#define MoveElevatorToHeight_H

#include "../CommandBase.h"

class MoveElevatorToHeight : public CommandBase {
public:
	MoveElevatorToHeight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // MoveElevatorToHeight_H
