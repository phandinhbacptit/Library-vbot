/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnBle
 * \brief   Driver for Vn Buzzer module.
 * @file    VnBle.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnBle.cpp module
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
 * This file is a drive for Vn Buzzer device, The Vn Buzzer inherited the 
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
 *
 *    1. void VnBle::setpin(int pin);
 *	  2. void VnBle::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnBle::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnBle::noTone(int pin);
 *	  5. void VnBle::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#ifndef VnBle_H
#define VnBle_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>
#include <stdlib.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID           "eb1435b7-d819-4ce9-acd8-a35b9d8f5e53" // UART service UUID
#define CHARACTERISTIC_UUID_RX "eb1435b8-d819-4ce9-acd8-a35b9d8f5e53"
#define CHARACTERISTIC_UUID_TX "eb1435b9-d819-4ce9-acd8-a35b9d8f5e53"

extern bool deviceConnected;
extern bool oldDeviceConnected;

class VnBle : public BLEDevice {
public:
  void VnBleInit(std::string bleName);
  void write(std::string data);
  void autoConnect(void);
};

class VnBleStatusConnect: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class VnBleRead: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
          Serial.print(rxValue[i]);
          Serial.println();
      }
    }
};


#endif
