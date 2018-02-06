/*
 * SilkyMotionManager.cpp
 *
 * We assume linear can be carried forward into next step, but always assume there is no angular velocity going into the next one.
 *
 *  Created on: Jan 28, 2017
 *      Author: sam_000
 */

#include <cmath>
#include <iostream>

#include "SmartDashboard/SmartDashboard.h"
#include "Components/SilkyMotionManager.h"

PathInfo SilkyMotionManager::getCurrentPathInfo(double t) {
	PathInfo pi; // dis, ang, lin_vel, lin_accel, ang_vel
	double time = 0;
	double totalTime = 0;
//	double dist = 0;
	double angle = 0;
	double startSpeed = 0;
	double endSpeed = 0;
	for (unsigned int i = 1; i < timestamps.size(); i++) {
		if ((t > timestamps[i - 1]) && (t < timestamps[i])) {
			time = t - timestamps[i - 1];
			totalTime = timestamps[i] - timestamps[i - 1];
			angle = ang[i - 1];
//			dist = dis[i - 1];
			startSpeed = actualSpeed[i - 1];
			endSpeed = actualSpeed[i];
		}
	}
	// TODO if t is past all timestamps need to do something special
	pi.ang_vel = angle / totalTime;
	pi.ang = pi.ang_vel * time;
	pi.lin_accel = (endSpeed - startSpeed) / totalTime; // assuming const accel
	pi.lin_vel = pi.lin_accel * time + startSpeed;
	pi.dis = startSpeed * time + 0.5 * pi.lin_accel * pow(time, 2);

	return pi;
}

double SilkyMotionManager::getAngularTime(double angle) {
	//have to do hard math
	//assuming we can ignore acceleration, deceleration, and angular component
	return (angle / maxAngVel);
}

double SilkyMotionManager::getLinearTime(double dis, double startSpeed, double endSpeed) {
	//have to do hard math
	//could go a lot faster using max accel and max decel


	//Assuming no crazy curves in spline, and giving reasonable headroom for acceleration + speed. We will tell program "max" is actually lower than max, since we are only programming for the left side. If the right side needs to turn faster than the right, the combination of a smaller max and a reasonable curvature will allow it to get ahead.
	//This means the left side will go "as fast as possible" in this model.
	double adjustedMaxVel = maxLinVel;

	double disToMaxVel = 0.5 * pow(maxLinVel - startSpeed , 2) / maxLinAccel;
	double disToEndVel = 0.5 * pow(maxLinVel - endSpeed, 2) / maxLinDecel;
	if (disToMaxVel + disToEndVel > dis) {
		// Don't get to full speed, so triangle instead of trapezoid
		// d_accel = (v-startSpeed)^2/(2*a_accel)
		// d_decel = (v-endSpeed)v^2/(2*a_decel)
		// d_total = (v-startSpeed)^2/(2*a_accel) + (v-endSpeed)^2/(2*a_decel)
		// Rearranging for v gives
		adjustedMaxVel = (sqrt(2 * dis * maxLinAccel * maxLinDecel) + startSpeed * sqrt(maxLinDecel) + endSpeed * sqrt(maxLinAccel)) / (sqrt(maxLinAccel) + sqrt(maxLinDecel));
		disToMaxVel = 0.5 * pow(adjustedMaxVel - startSpeed, 2) / maxLinAccel;
		disToEndVel = 0.5 * pow(adjustedMaxVel - endSpeed, 2) / maxLinDecel;
	}
	double timeToMaxVel = (adjustedMaxVel - startSpeed) / maxLinAccel;
	double timeAtMaxVel = (dis - disToMaxVel - disToEndVel) / adjustedMaxVel;

	double timeToEnd = (adjustedMaxVel - endSpeed)  / maxLinDecel;

	return timeToEnd + timeToMaxVel + timeAtMaxVel;
}

// Getting the absolute fastest we can start the current motion, given the absolute fastest we can be going at the end of the motion.
// For now, using simplifying assumptions that it is just the lowest of (A) linear decel required and (B) max centripetal force
double SilkyMotionManager::getMaxSpeed(double dis, double ang, double maxEndSpeed) {
	double radius = dis/(ang*M_PI/180.0); // Converting to radians to get radius of curvature
	double angularMax = sqrt(maxAngAccel * radius);

	// vf^2 = vi^2 + 2*a*d
	double linearMax = sqrt(pow(maxEndSpeed,2) + 2*maxLinDecel*dis);
	return std::min({angularMax, linearMax, maxLinVel});
}

// How fast can we be going when we end the current motion, given how fast we started the motion and how fast we are allowed to end it.
// For now, using simplifying assumption that it is just based on linear acceleration, ignoring angular stuff.
double SilkyMotionManager::getActualSpeed(double dis, double ang, double startingActualSpeed, double maxEndSpeed) {
	// vf^2 = vi^2 + 2*a*d
	double maxAchievableSpeed = sqrt(pow(startingActualSpeed,2) + 2*maxLinAccel*dis);
	return std::min(maxAchievableSpeed, maxEndSpeed);
}

double SilkyMotionManager::getTimestamp(double dis, double ang, double startingSpeed, double endingSpeed, double prevTime) {
	return prevTime + getAngularTime(ang) + getLinearTime(dis, startingSpeed, endingSpeed);
}

void SilkyMotionManager::setFeedbackConstants(double dis_v, double dis_a, double dis_p, double dis_d,
		double ang_v, double ang_a, double ang_p, double ang_d) {
	this->dis_a = dis_a;
	this->dis_v = dis_v;
	this->dis_p = dis_p;
	this->dis_d = dis_d;

	this->ang_a = ang_a;
	this->ang_v = ang_v;
	this->ang_p = ang_p;
	this->ang_d = ang_d;
}

std::pair<double, double> SilkyMotionManager::execute(double currentLeftPos, double currentRightPos){
	return std::make_pair(1.0, 1.0);
}

bool SilkyMotionManager::isFinished(double leftPos, double leftVel, double rightPos, double rightVel, double angle){
	return false;
}

void SilkyMotionManager::reset(){

}

SilkyMotionManager::SilkyMotionManager(std::vector<double> dis, std::vector<double> ang,
			double maxLinAccel, double maxLinDecel, double maxLinVel,
			double maxAngAccel, double maxAngDecel, double maxAngVel,
			double stoppingDistanceTolerance, double stoppingSpeedTolerance,
			double stoppingAngleTolerance) :
			dis(dis), ang(ang), maxLinAccel(maxLinAccel), maxLinDecel(maxLinDecel), maxLinVel(maxLinVel),
			maxAngAccel(maxAngAccel), maxAngDecel(maxAngDecel), maxAngVel(maxAngVel),
			stoppingDistanceTolerance(stoppingDistanceTolerance),
			stoppingSpeedTolerance(stoppingSpeedTolerance),
			stoppingAngleTolerance(stoppingAngleTolerance),
			dis_v(0), dis_a(0), dis_p(0), dis_d(0),
			ang_v(0), ang_a(0), ang_p(0), ang_d(0),
			lastDistanceError(0), lastAngleError(0),
			startTime(-1),
			lastTime(0) {
		maxSpeed.resize(dis.size() + 1);
		maxSpeed[maxSpeed.size() - 1] = 0;
		for(unsigned int i = dis.size(); i>=0; i--){
			maxSpeed[i] = getMaxSpeed(dis[i], ang[i], maxSpeed[i+1]);
		}
		actualSpeed.resize(dis.size() + 1);
		actualSpeed[0] = 0;
		timestamps.resize(dis.size() + 1);
		timestamps[0] = 0;
		for(unsigned int i = 1; i != dis.size(); i++){
			actualSpeed[i] = getActualSpeed(dis[i], ang[i], actualSpeed[i-1], maxSpeed[i]);
			timestamps[i] = getTimestamp(dis[i], ang[i], actualSpeed[i-1], actualSpeed[i], timestamps[i-1]);
		}
}

