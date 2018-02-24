#ifndef SilkyMotionCmd_H
#define SilkyMotionCmd_H
#include <vector>
#include  "Components/SilkyMotionManager.h"
#include "../CommandBase.h"

const double MAX_LIN_ACCEL=1475.0;
const double MAX_LIN_DECEL=3000.0;
const double MAX_LIN_VEL=3000.0;
const double MAX_ANG_ACCEL=250.0;
const double MAX_ANG_DECEL=10.0;
const double MAX_ANG_VEL=70.0;
const double STOPPING_DISTANCE_TOLERANCE=1.0;
const double STOPPING_SPEED_TOLERANCE=1.0;
const double STOPPING_ANGLE_TOLERANCE=1.0;

class SilkyMotionCmd : public CommandBase {
public:
	SilkyMotionCmd(std::vector<double> dis, std::vector<double> ang);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	SilkyMotionManager smm;
};

#endif  // SilkyMotionCmd_H
