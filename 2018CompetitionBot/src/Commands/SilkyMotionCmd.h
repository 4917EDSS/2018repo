#ifndef SilkyMotionCmd_H
#define SilkyMotionCmd_H
#include <vector>
#include  "Components/SilkyMotionManager.h"
#include "../CommandBase.h"

const double MAX_LIN_ACCEL=1475.0;
const double MAX_LIN_DECEL=3000.0;
const double MAX_LIN_VEL=3000.0;
const double MAX_ANG_ACCEL=500.0;

const double P_DIS=0.0076;
const double D_DIS=0.00002;
const double A_DIS=(1.0/MAX_LIN_DECEL)*0.485;
const double V_DIS=(1.0/MAX_LIN_ACCEL)*0.87;
const double P_ANG=0.001;
const double V_ANG=0.001;

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
	double prevError;
	double prevTime;
};

#endif  // SilkyMotionCmd_H
