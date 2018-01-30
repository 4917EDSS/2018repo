#ifndef DriveWithJoystickCmd_H
#define DriveWithJoystickCmd_H

#include "../CommandBase.h"


class DriveWithJoystickCmd : public CommandBase {
public:
	DriveWithJoystickCmd();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	int wasDrivingStraight;
	uint64_t timeSinceDrivingStraight;
};

#endif  // DriveWithJoystickCmd_H
