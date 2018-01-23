#ifndef SetHighGearHeldCmd_H
#define SetHighGearHeldCmd_H

#include "../CommandBase.h"

class SetHighGearHeldCmd : public CommandBase {
public:
	SetHighGearHeldCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OpenCompressorsHeldCmd_H
