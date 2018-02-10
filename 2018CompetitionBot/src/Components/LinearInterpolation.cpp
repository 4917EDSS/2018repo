/*
 * LinearInterpolation.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Melissa
 */

#include <Components/LinearInterpolation.h>

LinearInterpolation4917::LinearInterpolation4917(const std::vector<DataPoints> &_table):table(_table) {
	// TODO Auto-generated constructor stub

}

double LinearInterpolation4917::computeX(double y) {
	if (y < table[0].y) {
		// TODO add log indicating value outside of table
		return table[0].x;
	}
	for(unsigned int i = 0; i < table.size() - 1; i++){
		if ((y >= table[i].y) && (y < table[i+1].y)){
			double x = (y - table[i].y) * (table[i+1].x - table[i].x) / (table[i+1].y - table[i].y);
			return table[i].x + x;
		}
	}
	// TODO add log indicating value outside of table
	return table[table.size() - 1].x;
}
