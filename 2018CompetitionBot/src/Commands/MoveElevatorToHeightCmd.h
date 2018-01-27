#ifndef MoveElevatorToHeight_H
#define MoveElevatorToHeight_H

#include "../CommandBase.h"

class MoveElevatorToHeightCmd : public CommandBase {
public:
	MoveElevatorToHeightCmd(double height);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double height;
};

#endif  // MoveElevatorToHeight_H
