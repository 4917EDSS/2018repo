/*
 * GlobalLogging.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Administrator
 */

#ifndef SRC_COMPONENTS_LOGGING_GLOBALLOGGING_H_
#define SRC_COMPONENTS_LOGGING_GLOBALLOGGING_H_

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Components/Logging/Log.h"

class GlobalLogging {
public:
	GlobalLogging();
	void logPeriodicValues();
private:
	frc::PowerDistributionPanel *pdp;
};
extern GlobalLogging globalLogging;

#endif /* SRC_COMPONENTS_LOGGING_GLOBALLOGGING_H_ */
