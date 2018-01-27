/*
 * AutoSwitch.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoSwitch.h>
#include <Commands/AutoSwitchLeftGrp.h>
#include <Commands/AutoSwitchRightGrp.h>
#include "iostream"
namespace frc4917 {

AutoSwitch::AutoSwitch() {
	// TODO Auto-generated constructor stub

}
frc::Command* AutoSwitch::getCommand(){
	if (ourSwitchIsRight) {
		return new AutoSwitchRightGrp();
	}
	else {
		return new AutoSwitchLeftGrp();
	}
}

} /* namespace frc4917 */
