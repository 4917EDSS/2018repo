/*
 * AutoScaleRight.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoScaleRight.h>
#include <Commands/AutoScaleRightGrp.h>
#include <Commands/AutoScaleRightToLeftGrp.h>


namespace frc4917 {

AutoScaleRight::AutoScaleRight() {
	// TODO Auto-generated constructor stub

}
frc::Command* AutoScaleRight::getCommand(){
	if (scaleIsRight){
		return new AutoScaleRightGrp();
	}
	else{
		return new AutoScaleRightToLeftGrp();
	}
}

} /* namespace frc4917 */
