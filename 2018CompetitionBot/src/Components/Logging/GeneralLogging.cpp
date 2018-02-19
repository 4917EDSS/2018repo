/*
 * GeneralLogging.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Administrator
 */

#include <Components/Logging/GeneralLogging.h>
#include <iostream>
#include <sstream>

GeneralLogging logging; // this is the global instance

GeneralLogging::GeneralLogging() {
	// TODO Auto-generated constructor stub
	pdp = new frc::PowerDistributionPanel;
}

void GeneralLogging::logPowerStuff() {
	std::stringstream line;
	line << "pdp channels V:" << pdp->GetVoltage() << " T:" << pdp->GetTemperature();
	for(int i = 0; i < 16; i++) {
		line << ", " << pdp->GetCurrent(i);
	}
	logger.send(logger.POWER, "%s\n", line.str().c_str());
}
