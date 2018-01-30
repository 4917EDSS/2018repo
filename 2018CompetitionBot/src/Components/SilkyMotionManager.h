/*
 * SilkyMotionManager.h
 *
 *  Created on: Jan 28, 2017
 *      Author: sam_000
 *
 *  Thanks 2702! :)
 */

#ifndef SRC_COMPONENTS_SILKYMOTIONMANAGER_H_
#define SRC_COMPONENTS_SILKYMOTIONMANAGER_H_

#include <vector>
#include <utility>
#include "WPILib.h"


struct PathInfo {
	double dis;
	double ang;
	double lin_vel;
	double lin_accel;
	double ang_vel;
	double ang_accel;
};

class SilkyMotionManager {
private:
	std::vector<double> maxSpeed;
	std::vector<double> actualSpeed;
	std::vector<double> timestamps;
	std::vector<double> dis;
	std::vector<double> ang;
	double maxLinAccel, maxLinDecel, maxLinVel;
	double maxAngAccel, maxAngDecel, maxAngVel;
	double stoppingDistanceTolerance, stoppingSpeedTolerance, stoppingAngleTolerance;
	double dis_v, dis_a, dis_p, dis_d;
	double ang_v, ang_a, ang_p, ang_d;

	double lastDistanceError;
	double lastAngleError;
	double startTime;
	double lastTime;

	double getTimeSinceStart();
	PathInfo getLeftSide(double t);
	PathInfo getRightSide(double t);

	double getTotalTime();
	double getAngularTime();
	double getLinearTime();

	double getMaxSpeed(double dis, double ang, double maxEndSpeed);
	double getActualSpeed(double dis, double ang, double startingActualSpeed, double maxEndSpeed);
	double getTimestamp(double dis, double ang, double startingSpeed, double endingSpeed, double prevTime);
public:
	SilkyMotionManager(std::vector<double> dis, std::vector<double> ang,
			double maxLinAccel, double maxLinDecel, double maxLinVel,
			double maxAngAccel, double maxAngDecel, double maxAngVel,
			double stoppingDistanceTolerance, double stoppingSpeedTolerance,
			double stoppingAngleTolerance);


	void setFeedbackConstants(double dis_v, double dis_a, double dis_p, double dis_d,
			double ang_v, double ang_a, double ang_p, double ang_d);
	std::pair<double, double> execute(double currentLeftPos, double currentRightPos); // returns left speed, right speed to set motors
	bool isFinished(double leftPos, double leftVel, double rightPos, double rightVel, double angle);
	void reset();
};

#endif /* SRC_COMPONENTS_SILKYMOTIONMANAGER_H_ */
