#ifndef ResetAHRSCmd_H
#define ResetAHRSCmd_H

#include "../CommandBase.h"

class ResetAHRSCmd : public CommandBase {
public:
	ResetAHRSCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ResetAHRSCmd_H
