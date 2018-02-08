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
};

#endif  // IntakeeUntilDistanceCmd_H
