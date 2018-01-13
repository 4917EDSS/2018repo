/*
 * AutoScaleRight.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#ifndef SRC_COMPONENTS_AUTODECIDER_AUTOSCALERIGHT_H_
#define SRC_COMPONENTS_AUTODECIDER_AUTOSCALERIGHT_H_

#include <WPILib.h>
#include <Components/AutoDecider/AutoDecider.h>

namespace frc4917 {

class AutoScaleRight: public AutoDecider {
public:
	AutoScaleRight();
	frc::Command* getCommand();
};

} /* namespace frc4917 */

#endif /* SRC_COMPONENTS_AUTODECIDER_AUTOSCALERIGHT_H_ */
