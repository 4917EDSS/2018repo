#ifndef ReverseIntakeCmd_H
#define ReverseIntakeCmd_H

#include "../CommandBase.h"

class ReverseIntakeCmd : public CommandBase {
public:
	ReverseIntakeCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ReverseIntakeCmd_H
