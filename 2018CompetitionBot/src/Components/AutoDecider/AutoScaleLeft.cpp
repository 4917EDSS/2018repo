/*
 * AutoScaleLeft.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoScaleLeft.h>
#include <Commands/AutoScaleLeftGrp.h>
#include <Commands/AutoScaleLeftToRightGrp.h>


namespace frc4917 {

AutoScaleLeft::AutoScaleLeft() {
	// TODO Auto-generated constructor stub

}
frc::Command* AutoScaleLeft::getCommand(){
	if (!scaleIsRight){
		return new AutoScaleLeftGrp();
	}
	else{
		return new AutoScaleLeftToRightGrp();
	}
}

} /* namespace frc4917 */
