/*
 * LinearInterpolation.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Melissa
 */

#ifndef SRC_COMPONENTS_LINEARINTERPOLATION_H_
#define SRC_COMPONENTS_LINEARINTERPOLATION_H_

#include <vector>

struct DataPoints {
	double x;
	double y;
};

class LinearInterpolation4917 {
public:
	// assuming that y values are monotonically increasing in the data table
	LinearInterpolation4917(const std::vector<DataPoints> &_table);
	// y must be >= first table entry and < last table entry
	double computeX(double y);
private:
	std::vector<DataPoints> table;
};

#endif /* SRC_COMPONENTS_LINEARINTERPOLATION_H_ */
