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

double SilkyMotionManager::getTotalTime(){
	return getAngularTime() + getLinearTime();
}

double SilkyMotionManager::getAngularTime() {
	//have to do hard math
	return (1.0);
}

double SilkyMotionManager::getLinearTime() {
	//have to do hard math
	return (1.0);
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

double getTimestamp(double dis, double ang, double startingSpeed, double endingSpeed, double prevTime) {
	return 0.0;
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

