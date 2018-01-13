/*
 * AutoScaleBackupSwitchLeft.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoScaleBackupSwitchLeft.h>
#include <Components/AutoDecider/AutoScaleRight.h>
#include <Components/AutoDecider/AutoScaleLeft.h>
#include <Commands/AutoScaleLeftGrp.h>
#include <Commands/AutoLeftToLeftSwitchGrp.h>
#include <Commands/AutoLeftToRightSwitchGrp.h>


namespace frc4917 {

AutoScaleBackupSwitchLeft::AutoScaleBackupSwitchLeft() {
	// TODO Auto-generated constructor stub

}
frc::Command* AutoScaleBackupSwitchLeft::getCommand() {
	if (!scaleIsRight){
		return new AutoScaleLeftGrp();
	}
	else if (!ourSwitchIsRight){
		return new AutoLeftToLeftSwitchGrp();
	}
	else{
		return new AutoLeftToRightSwitchGrp();
	}

}
} /* namespace frc4917 */
