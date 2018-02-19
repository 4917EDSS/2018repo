/*
 * GeneralLogging.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Administrator
 */

#ifndef SRC_COMPONENTS_LOGGING_GENERALLOGGING_H_
#define SRC_COMPONENTS_LOGGING_GENERALLOGGING_H_

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Components/Logging/Log.h"

class GeneralLogging {
public:
	GeneralLogging();
	void logPowerStuff();
private:
	frc::PowerDistributionPanel *pdp;
};
extern GeneralLogging logging;

#endif /* SRC_COMPONENTS_LOGGING_GENERALLOGGING_H_ */
