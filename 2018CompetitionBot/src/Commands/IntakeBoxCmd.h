#ifndef RunIntakeCmd_H
#define RunIntakeCmd_H

#include "../CommandBase.h"

class IntakeBoxCmd : public CommandBase {
public:
	IntakeBoxCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RunIntakeCmd_H
