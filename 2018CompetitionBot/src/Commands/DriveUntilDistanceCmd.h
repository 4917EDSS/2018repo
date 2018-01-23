#ifndef DriveUntilDistanceCmd_H
#define DriveUntilDistanceCmd_H

#include "../CommandBase.h"

class DriveUntilDistanceCmd : public CommandBase {
private:
	double targetDistance;

public:
	DriveUntilDistanceCmd(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveUntilDistanceCmd_H
