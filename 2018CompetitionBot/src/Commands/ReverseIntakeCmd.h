#ifndef ReverseIntakeCmd_H
#define ReverseIntakeCmd_H

#include "../CommandBase.h"

class ReverseIntakeCmd : public CommandBase {
public:
	ReverseIntakeCmd(double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double timeExpelling;
};

#endif  // ReverseIntakeCmd_H
