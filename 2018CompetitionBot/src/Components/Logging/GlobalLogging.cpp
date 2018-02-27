/*
 * GlobalLogging.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Administrator
 */

#include <Components/Logging/GlobalLogging.h>
#include <iostream>
#include <sstream>


GlobalLogging globalLogging; // this is the global instance

GlobalLogging::GlobalLogging() {
	pdp = new frc::PowerDistributionPanel;
}

void GlobalLogging::logPeriodicValues() {
	std::stringstream line;

	// Prefix the line with "LP:" for log-periodic so we can filter on that
	// Use tabs (\t)to separate fields to make it easy to import into a spreadsheet
	line << "LP:Global\tPDP\tVolt\t" << pdp->GetVoltage() << "Temp\t" << pdp->GetTemperature();
	for(int i = 0; i < 16; i++) {
//		line << "\tCH" << i << " C\t" << pdp->GetCurrent(i);	// TODO: Fix. This gives a timeout error
	}

	logger.send(logger.PERIODIC, "%s\n", line.str().c_str());
}
