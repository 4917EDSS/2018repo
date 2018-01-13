/*
 * LidarLite.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Gaudets
 */

#ifndef SRC_COMPONENTS_LIDARLITE_H_
#define SRC_COMPONENTS_LIDARLITE_H_

#include "WPILib.h"

class LidarLite {
private:
	std::unique_ptr<frc::I2C> comms;
public:
	LidarLite();
	virtual ~LidarLite();
	double getDistance();
};

#endif /* SRC_COMPONENTS_LIDARLITE_H_ */
