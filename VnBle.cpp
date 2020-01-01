#include "VnBle.h"

BLEServer *VnServer = NULL;
BLEService *VnService = NULL;
BLECharacteristic *VnBleTx = NULL;
BLECharacteristic *VnBleRx = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

void VnBle::VnBleInit(std::string bleName)
{
	/*Init name of Bluetooth device to use*/
	init(bleName);
	/*Create the BLE Server*/
	VnServer = createServer();
	VnServer->setCallbacks(new VnBleStatusConnect());
	/*Create the BLE Service*/
	VnService = VnServer->createService(SERVICE_UUID);
	/*Create the BLE Characteristic*/
	VnBleTx = VnService->createCharacteristic (CHARACTERISTIC_UUID_TX, BLECharacteristic :: PROPERTY_READ);

	VnBleTx->addDescriptor(new BLE2902());
	
	VnBleRx = VnService->createCharacteristic (CHARACTERISTIC_UUID_RX, BLECharacteristic :: PROPERTY_WRITE);
	VnBleRx->setCallbacks(new VnBleRead());
	
	/*Start BLE service*/
	VnService->start();
	
	/*Start advertising*/
	VnServer->getAdvertising()->start();
	Serial.println("Ble devive ready, waitting a client connection ...");
}

void VnBle::write(std::string data)
{
	if (deviceConnected) {
		VnBleTx->setValue(data);
		VnBleTx->notify();
	} 
	else {
		Serial.println("Not connect with bluetooth device!");
	}
	 
}
	
void VnBle::autoConnect(void)
{
	if (!deviceConnected && oldDeviceConnected) {
       delay(500); // give the bluetooth stack the chance to get things ready
       VnServer->startAdvertising(); // restart advertising
       Serial.println("start advertising");
       oldDeviceConnected = deviceConnected;
   }

   if (deviceConnected && !oldDeviceConnected) {
       oldDeviceConnected = deviceConnected;
   }
	
}