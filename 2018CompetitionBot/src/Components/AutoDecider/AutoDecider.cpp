/*
 * CAutoDecider.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoDecider.h>

namespace frc4917 {




AutoDecider::AutoDecider() {
	// TODO Auto-generated constructor stub
	ourSwitchIsRight = false;
	scaleIsRight = false;
	oppSwitchIsRight = false;
}

AutoDecider::~AutoDecider() {}

void AutoDecider::setGameData(std::string gameData) {
	//determine side of our switch, opponents switch, and scale
	ourSwitchIsRight = false;
	scaleIsRight = false;
	oppSwitchIsRight = false;

	if (gameData[0] == 'R') {
		ourSwitchIsRight = true;
	}
	if (gameData[1] == 'R') {
		scaleIsRight = true;
	}
	if (gameData[2] == 'R') {
		oppSwitchIsRight = true;
	}
}




} /* namespace frc4917 */
