/*
 * LinearInterpolation.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Melissa
 */

#include <Components/LinearInterpolation.h>

LinearInterpolation::LinearInterpolation(std::vector<DataPoints> _table):table(_table) {
	// TODO Auto-generated constructor stub

}

double LinearInterpolation::computeX(double y) {
	for(auto i: table){
		if (y >= i.y){
//			double x = (y - i.y) * ((i+1).x - i.x) / ((i+1).y - i.y);
//			return i.x + x;
		}
	}
	return -1;
}
