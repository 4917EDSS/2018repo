#ifndef DropBoxCmd_H
#define DropBoxCmd_H

#include "../CommandBase.h"

class DropBoxCmd : public CommandBase {
public:
	DropBoxCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DropBoxCmd_H
