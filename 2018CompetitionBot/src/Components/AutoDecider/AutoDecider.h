/*
 * CAutoDecider.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#ifndef SRC_COMPONENTS_CAUTODECIDER_H_
#define SRC_COMPONENTS_CAUTODECIDER_H_
#include <string>
#include <WPILib.h>

namespace frc4917 {

class AutoDecider {
protected:
	bool ourSwitchIsRight;
	bool scaleIsRight;
	bool oppSwitchIsRight;

public:
	AutoDecider();
	virtual ~AutoDecider();
	void setGameData(std::string gameData);
	virtual frc::Command* getCommand() = 0;
};


} /* namespace frc4917 */

#endif /* SRC_COMPONENTS_CAUTODECIDER_H_ */
