/*
 * LidarLite.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Gaudets
 */

#include <Components/LidarLite.h>

constexpr int LIDARLITE_ADDR = 0x62;

LidarLite::LidarLite() {
	// TODO Auto-generated constructor stub
	comms.reset(new I2C(frc::I2C::kOnboard, LIDARLITE_ADDR));
}

LidarLite::~LidarLite() {
	// TODO Auto-generated destructor stub
}

double LidarLite::getDistance() {
	uint8_t status;
	uint8_t data[2];
	int tries = 500;
	uint16_t distanceInCm;

	// Initiate measurement
	comms->Write(0x00, 0x04);

	// Wait for measurement to complete
	do {
		comms->Read(0x01, 1, &status);
	} while((status & 0x01) && (--tries > 0));

	// Get 16-bit measurement as two 8-bit bytes. MSB in first byte
	comms->Read(0x8f, 2, data);
	distanceInCm = ((uint16_t)data[0] << 8) | data[1];

	// Convert cm to mm
	return distanceInCm * 10.0;
}
