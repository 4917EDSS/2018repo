#include "../SilkyMotionManager.h"
#include <vector>
#include <iostream>
// g++ -std=c++11 test.cpp ../SilkyMotionManager.cpp

/*
int main() {
//  SilkyMotionManager smm(std::vector<double> {3000, 1000, 3500, 2000},
  //    std::vector<double> {0, 90, 0 , -110}, 1475.0, 3000.0, 2950.0, 500.0);
  //SilkyMotionManager smm(std::vector<double> {100, 200, 600, 3000}, std::vector<double> {90, 0, 0, -45}, 1475.0, 3000.0, 2950.0, 500.0);
  //SilkyMotionManager smm(std::vector<double> {500, 2000, 6000, 300, 100}, std::vector<double> {70, -10, 80, -45, -10}, 1475.0, 3000.0, 2950.0, 500.0);
  SilkyMotionManager smm(std::vector<double> {4380, 2000, 4000, 2200}, std::vector<double> {0, -90, 0, 150}, 1475.0, 3000.0, 2950.0, 800.0);
  std::cout << "time, dis, ang, lin_vel, lin_accel, ang_vel" << std::endl;

  for (double t = 0; t <= smm.getTotalTime()+0.03; t += 0.02) {
    PathInfo pi = smm.getCurrentPathInfo(t);
    std::cout << t << ", " << pi.dis << ", " << pi.ang << ", " << pi.lin_vel << ", " << pi.lin_accel << ", " << pi.ang_vel << std::endl;
  }
}
*/
