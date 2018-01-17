#ifndef OpenCompressorsHeldCmd_H
#define OpenCompressorsHeldCmd_H

#include "../CommandBase.h"

class OpenCompressorsHeldCmd : public CommandBase {
public:
	OpenCompressorsHeldCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OpenCompressorsHeldCmd_H
