#ifndef ResetEncodersCmd_H
#define ResetEncodersCmd_H

#include "../CommandBase.h"

class ResetEncodersCmd : public CommandBase {
public:
	ResetEncodersCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ResetEncodersCmd_H
