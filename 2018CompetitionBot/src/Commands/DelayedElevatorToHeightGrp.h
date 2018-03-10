#ifndef DelayedElevatorToHeightGrp_H
#define DelayedElevatorToHeightGrp_H

#include <Commands/CommandGroup.h>

class DelayedElevatorToHeightGrp : public CommandGroup {
public:
	DelayedElevatorToHeightGrp(double time, double height);

};
#endif
