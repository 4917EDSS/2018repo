#ifndef IntakeUntilDistanceCmd_H
#define IntakeUntilDistanceCmd_H

#include "../CommandBase.h"

class IntakeUntilLimitCmd : public CommandBase {

public:
	IntakeUntilLimitCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool jawsSetToSpring;
	double lastMoveTime = 0;
	double lastAtJaws = 0;
};

#endif  // IntakeeUntilDistanceCmd_H
