#ifndef OpenCompressorsCmd_H
#define OpenCompressorsCmd_H

#include "../CommandBase.h"

class OpenCompressorsCmd : public CommandBase {
private:
	bool directionOpen;

public:
	OpenCompressorsCmd();
	OpenCompressorsCmd(bool b);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OpenCompressorsCmd_H
