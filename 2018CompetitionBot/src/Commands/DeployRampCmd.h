#ifndef DeployRampCmd_H
#define DeployRampCmd_H

#include "../CommandBase.h"

class DeployRampCmd : public CommandBase {
public:
	DeployRampCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DeployRampCmd_H
