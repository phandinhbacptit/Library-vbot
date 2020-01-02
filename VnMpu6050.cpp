/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnMpu6050
 * \brief   Driver for Vn Mpu6050 module.
 * @file    VnMpu6050.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2020/1/1
 * @brief   Driver for Vn Mpu6050 module.
 *
 * @ Copyright
 * This software is Copyright (C), 2018-2020, Vrobotx. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @ Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @Brief :
 * This file is a drive for Vn Mpu6050 device, The Vn Mpu6050 inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
 *
 *    1. VnMpu6050::VnMpu6050(void);
 *	  2. VnMpu6050::VnMpu6050(uint8_t port):VnPort(port);
 *	  3. void VnMpu6050::init(uint16_t freq);
 *	  4. void VnMpu6050:: accRead(float *accX, float *accY, float *accZ);
 *	  5. void VnMpu6050::gyroRead(float *gyroX, float *gyroY, float *gyroZ);
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2020/1/1      1.0.0            Build the first library.
 * </pre>
 */
#include "VnMpu6050.h"
#include "Wire.h"


#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Mpu6050 to arduino port,
 * Mpu6050 pins are used and initialized here.
 * @Param : None
 */
VnMpu6050::VnMpu6050(void)
{
	_sclPin = 21;
	_sdaPin = 22;
}

/**
 * Alternate Constructor which can call your own function to map the Mpu6050 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnMpu6050::VnMpu6050(uint8_t port):VnPort(port)
{
	_sclPin = s1;
	_sdaPin = s2;
}

#else // VN_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the Mpu6050 to arduino port,
 * @Param :  switchPin - arduino port for Mpu6050 detect pin.
 */
VnMpu6050::VnMpu6050(uint8_t scl_pin, uint8_t sda_pin)
{
	_sclPin = scl_pin;
	_sdaPin = sda_pin;
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Init protocol communicate between MPU6050 and ESP32
 * @Param :  freq - Speed communicating I2C
 * @Retval : None.
 * @Others : 
 */
void VnMpu6050::init(uint16_t freq)
{
	Wire.begin(_sclPin, _sdaPin, freq); // Initialize comunication
	Wire.beginTransmission(MPU_ADDR);   // Start communication with MPU6050 // MPU=0x68
	Wire.write(MPU_PWR_MGMT_1);         // Talk to the register MPU_PWR_MGMT_1
	Wire.write(0x00);                  	// Make reset - place a 0 into the 6B register
	Wire.endTransmission(true);        	//end the transmission
}

/**
 * @Brief :  Read accelerometer value from MPU6050. This function will read 6 registers total, each axis value is stored in 2 registers. 
 *			 Start at register ACCEL_XOUT_H
 * @Param :  accX - contain Accelerometer X axis
 *           accY - contain Accelerometer Y axis
 *           accZ - contain Accelerometer Z axis
 * @Retval : None.
 * @Others :
 */
void VnMpu6050:: accRead(float *accX, float *accY, float *accZ)
{
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(MPU_ACCEL_XOUT_H); 						// Start with register 0x3B (ACCEL_XOUT_H)
	Wire.endTransmission(false);
	Wire.requestFrom(MPU_ADDR, 6, true); 				// Read 6 registers total, each axis value is stored in 2 registers
	/* For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet*/
	*accX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
	*accY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
	*accZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
}
/**
 * @Brief :  This function caculate gyroscope rate  value from MPU6050. This function will read 6 registers total, each axis value is stored in 2 registers. 
 *			 Start at register GYRO_XOUT_H
 * @Param :  *rateRateX - contain Gyroscope X axis
 *           *rateRateY - contain Gyroscope Y axis
 *           *rateRateZ - contain Gyroscope Z axis
 *           *offGyroX - contain offset Gyroscope X axis
 *           *offGyroY - contain offset Gyroscope Y axis
 *           *offGyroZ - contain offset Gyroscope Z axis
 * @Retval : None.
 * @Others :
 */

void VnMpu6050::gyroRateGet(float *rateRateX, float *rateRateY, float *rateRateZ, float offGyroX, float offGyroY, float offGyroZ)
{
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(MPU_GYRO_XOUT_H); 						// Start with register 0x3B (ACCEL_XOUT_H)
	Wire.endTransmission(false);
	Wire.requestFrom(MPU_ADDR, 6, true); 				// Read 6 registers total, each axis value is stored in 2 registers
	/* For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet*/
	*rateRateX = (Wire.read() << 8 | Wire.read()) / 131.0 - offGyroX; // X-axis value
	*rateRateY = (Wire.read() << 8 | Wire.read()) / 131.0 - offGyroY; // Y-axis value
	*rateRateZ = (Wire.read() << 8 | Wire.read()) / 131.0 - offGyroZ; // Z-axis value
} 
/**
 * @Brief :  This function will get error values of accelerometer and gyroscope. The process will read value 200 times of sensor to caculate. 
 *			 Start at register ACCEL_XOUT_H
 * @Param :  offAccX  - The pointer point to value offset of Accelerometer X
 *			 offAccY  - The pointer point to value offset of Accelerometer Y
 *			 offAccZ  - The pointer point to value offset of Accelerometer Z
 *			 offGyroX - The pointer point to value offset of Gyroscope X
 *			 offGyroY - The pointer point to value offset of Gyroscope Y
 *			 offGyroZ - The pointer point to value offset of Gyroscope Z
 * @Retval : None.
 * @Others :
 */
void VnMpu6050::sensorOffsetGet(float *offAccX, float *offAccY, float *offGyroX, float *offGyroY, float *offGyroZ)
{
	float AccX = 0, AccY = 0, AccZ = 0;
	float GyroX = 0, GyroY = 0, GyroZ = 0;
	uint8_t c = 0;

	while (c < 200) {
		Wire.beginTransmission(MPU_ADDR);
		Wire.write(MPU_ACCEL_XOUT_H);
		Wire.endTransmission(false);
		Wire.requestFrom(MPU_ADDR, 6, true);
		AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
		AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
		AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
		*offAccX = *offAccX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
		*offAccY = *offAccY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
		c++;
	}

	*offAccX = *offAccX / 200;
	*offAccY = *offAccY / 200;
	c = 0;

	while (c < 200) {
		Wire.beginTransmission(MPU_ADDR);
		Wire.write(MPU_GYRO_XOUT_H);
		Wire.endTransmission(false);
		Wire.requestFrom(MPU_ADDR, 6, true);
		GyroX = Wire.read() << 8 | Wire.read();
		GyroY = Wire.read() << 8 | Wire.read();
		GyroZ = Wire.read() << 8 | Wire.read();

		*offGyroX = *offGyroX + (GyroX / 131.0);
		*offGyroY = *offGyroY + (GyroY / 131.0);
		*offGyroZ = *offGyroZ + (GyroZ / 131.0);
		c++;
	}

	*offGyroX = *offGyroX / 200;
	*offGyroY = *offGyroY / 200;
	*offGyroZ = *offGyroZ / 200;

	Serial.print("AccErrorX: ");
	Serial.println(*offAccX);
	Serial.print("AccErrorY: ");
	Serial.println(*offAccY);
	Serial.print("*offGyroX: ");
	Serial.println(*offGyroX);
	Serial.print("*offGyroY: ");
	Serial.println(*offGyroY);
	Serial.print("*offGyroZ: ");
	Serial.println(*offGyroZ);	
 }