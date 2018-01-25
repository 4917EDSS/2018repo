#ifndef RaiseRampCmd_H
#define RaiseRampCmd_H

#include "../CommandBase.h"

class RaiseRampCmd : public CommandBase {
public:
	RaiseRampCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RaiseRampCmd_H
