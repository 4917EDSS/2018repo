#ifndef HoldBoxCmd_H
#define HoldBoxCmd_H

#include "../CommandBase.h"

class HoldBoxCmd : public CommandBase {
public:
	HoldBoxCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // HoldBoxCmd_H
