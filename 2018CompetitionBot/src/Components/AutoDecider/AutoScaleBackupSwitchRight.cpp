/*
 * AutoScaleBackupSwitch.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoScaleLeft.h>
#include <Components/AutoDecider/AutoScaleRight.h>
#include <Commands/AutoScaleRightGrp.h>
#include <Commands/AutoRightToRightSwitchGrp.h>
#include <Commands/AutoRightToLeftSwitchGrp.h>
#include <Components/AutoDecider/AutoScaleBackupSwitchRight.h>


namespace frc4917 {

AutoScaleBackupSwitchRight::AutoScaleBackupSwitchRight() {
	// TODO Auto-generated constructor stub

}
frc::Command* AutoScaleBackupSwitchRight::getCommand(){
	if (scaleIsRight) {
		return new AutoScaleRightGrp();
	}
	else if (ourSwitchIsRight){
		return new AutoRightToRightSwitchGrp();
	}
	else{
		return new AutoRightToLeftSwitchGrp();
	}
}
}
 /* namespace frc4917 */
//1.Scale if on our side 2.go to nearest switch on our side
