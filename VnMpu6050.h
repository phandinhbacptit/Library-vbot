/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnMpu6050
 * \brief   Driver for Vn Mpu6050 module.
 * @file    VnMpu6050.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2020/1/1
 * @brief   Header for VnMpu6050.cpp module
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
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
 *
 *    1. void VnMpu6050::setpin(int pin);
 *	  2. void VnMpu6050::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnMpu6050::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnMpu6050::noTone(int pin);
 *	  5. void VnMpu6050::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2020/1/1          1.0.0            Build the first library.
 * </pre>
 */
#ifndef _VNMPU6050_H_
#define _VNMPU6050_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED
/**
 * Class: VnMpu6050
 * @Brief : Declaration of Class VnMpu6050.
 */
 
#define MPU_ADDR 		 	0x69
#define MPU_PWR_MGMT_1	 	0x6B

#define MPU_ACCEL_XOUT_H	0x3B
#define MPU_ACCEL_XOUT_L	0x3C
#define MPU_ACCEL_YOUT_H	0x3D
#define MPU_ACCEL_YOUT_L	0x3E
#define MPU_ACCEL_ZOUT_H	0x3F
#define MPU_ACCEL_ZOUT_L	0x40
 
#define MPU_GYRO_XOUT_H		0x43 
#define MPU_GYRO_XOUT_L		0x44
#define MPU_GYRO_YOUT_H		0x45 
#define MPU_GYRO_YOUT_L		0x46 
#define MPU_GYRO_ZOUT_H		0x47 
#define MPU_GYRO_ZOUT_L		0x48

#define X_AXIS_OFFSET		0
#define Y_AXIS_OFFSET		0
#define Z_AXIS_OFFSET		0
 
#ifdef VN_PORT_DEFINED
class VnMpu6050 : public VnPort
#else
class VnMpu6050
#endif
{
public:
#ifdef VN_PORT_DEFINED

	VnMpu6050(void);
	VnMpu6050(uint8_t port);
  
#else //VN_PORT_DEFINED

	VnMpu6050(uint8_t scl_pin, uint8_t sda_pin);

#endif //VN_PORT_DEFINED
	void init(uint16_t freq);
	void accRead(float *accX, float *accY, float *accZ);
	void gyroRateGet(float *rateRateX, float *rateRateY, float *rateRateZ, float offGyroX, float offGyroY, float offGyroZ);
    void sensorOffsetGet(float *offAccX, float *offAccY, float *offGyroX, float *offGyroY, float *offGyroZ);
private:
	volatile uint8_t  _sclPin;
	volatile uint8_t  _sdaPin;

};
#endif /* _VnMpu6050_H_ */