/*
 * CAutoDecider.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Software
 */

#include <Components/AutoDecider/AutoDecider.h>
#include "iostream"
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
		std::cout << "at 0 True" << std::endl;
		ourSwitchIsRight = true;
	}
	if (gameData[1] == 'R') {
		std::cout << "at 1 True" << std::endl;
		scaleIsRight = true;
	}
	if (gameData[2] == 'R') {
		std::cout << "at 2 True" << std::endl;
		oppSwitchIsRight = true;

	}
}




} /* namespace frc4917 */
