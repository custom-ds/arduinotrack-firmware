/*
BMP180.h

Copywrite 2011-2015 - Zack Clobes (W0ZC), Custom Digital Services, LLC
Based on the BMP180 from Mike Grusin at SparkFun Electronics.


This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef BMP180_h
#define BMP180_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class BMP180
{
	public:
		BMP180(); // base type

		char begin();
			// call pressure.begin() to initialize BMP180 before use
			// returns 1 if success, 0 if failure (bad component or I2C bus shorted?)
		
		char startTemperature(void);
			// command BMP180 to start a temperature measurement
			// returns (number of ms to wait) for success, 0 for fail

		char getTemperature(double &T);
			// return temperature measurement from previous startTemperature command
			// places returned value in T variable (deg C)
			// returns 1 for success, 0 for fail

		char startPressure(char oversampling);
			// command BMP180 to start a pressure measurement
			// oversampling: 0 - 3 for oversampling value
			// returns (number of ms to wait) for success, 0 for fail

		char getPressure(double &P, double &T);
			// return absolute pressure measurement from previous startPressure command
			// note: requires previous temperature measurement in variable T
			// places returned value in P variable (mbar)
			// returns 1 for success, 0 for fail

		double sealevel(double P, double A);
			// convert absolute pressure to sea-level pressure (as used in weather data)
			// P: absolute pressure (mbar)
			// A: current altitude (meters)
			// returns sealevel pressure in mbar

		double altitude(double P, double P0);
			// convert absolute pressure to altitude (given baseline pressure; sea-level, runway, etc.)
			// P: absolute pressure (mbar)
			// P0: fixed baseline pressure (mbar)
			// returns signed altitude in meters

		char getError(void);
			// If any library command fails, you can retrieve an extended
			// error code using this command. Errors are from the wire library: 
			// 0 = Success
			// 1 = Data too long to fit in transmit buffer
			// 2 = Received NACK on transmit of address
			// 3 = Received NACK on transmit of data
			// 4 = Other error

	private:
	
		char readInt(char address, int16_t &value);
			// read an signed int (16 bits) from a BMP180 register
			// address: BMP180 register address
			// value: external signed int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with result in value

		char readUInt(char address, uint16_t &value);
			// read an unsigned int (16 bits) from a BMP180 register
			// address: BMP180 register address
			// value: external unsigned int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with result in value

		char readBytes(unsigned char *values, char length);
			// read a number of bytes from a BMP180 register
			// values: array of char with register address in first location [0]
			// length: number of bytes to read back
			// returns 1 for success, 0 for fail, with read bytes in values[] array
			
		char writeBytes(unsigned char *values, char length);
			// write a number of bytes to a BMP180 register (and consecutive subsequent registers)
			// values: array of char with register address in first location [0]
			// length: number of bytes to write
			// returns 1 for success, 0 for fail
			
		int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
		uint16_t AC4,AC5,AC6; 
		double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
		char _error;
    unsigned long _milliTimeout;
};

#define BMP180_ADDR 0x77 // 7-bit address

#define	BMP180_REG_CONTROL 0xF4
#define	BMP180_REG_RESULT 0xF6

#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0 0x34
#define	BMP180_COMMAND_PRESSURE1 0x74
#define	BMP180_COMMAND_PRESSURE2 0xB4
#define	BMP180_COMMAND_PRESSURE3 0xF4

#define BMP180_TIMEOUT 250
#endif
