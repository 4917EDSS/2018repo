#ifndef RunIntakeCmd_H
#define RunIntakeCmd_H

#include "../CommandBase.h"

class RunIntakeCmd : public CommandBase {
public:
	RunIntakeCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RunIntakeCmd_H
