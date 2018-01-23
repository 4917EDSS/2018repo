#ifndef IntakeUntilDistanceCmd_H
#define IntakeUntilDistanceCmd_H

#include "../CommandBase.h"

class IntakeUntilDistanceCmd : public CommandBase {
private:
	double targetDistance;

public:
	IntakeUntilDistanceCmd(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // IntakeeUntilDistanceCmd_H
