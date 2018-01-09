#ifndef OI_H
#define OI_H

const int DRIVER_CONTROLLER_PORT = 0;

class OI {
public:
	OI();

private:
	std::shared_ptr<frc::Joystick> driverController;
};

#endif  // OI_H
