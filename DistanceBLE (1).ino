
#include <ArduinoBLE.h>
BLEService Distance("1101");
BLEUnsignedCharCharacteristic DistanceChar("1101", BLERead | BLENotify);

/*
The first line of the code is to include the ArduinoBLE.h file. 
Then we will declare the "Distance" Service as well the distance 
characteristics here. Here we will be 
giving two permissions  – BLERead and BLENotify. 

*/

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

/*
  Here it will initialize the Serial Communication 
  and BLE and wait for serial monitor to open. 
  Set a local name for the BLE device. 
  This name will appear in advertising packets and can be used 
  by remote devices to identify this BLE device.
*/

  BLE.setLocalName("PetTracker");
  BLE.setAdvertisedService(Distance);
  Distance.addCharacteristic(DistanceChar);
  BLE.addService(Distance);

// Here we will add and set the value for the Service UUID and the Characteristic.

  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
  /*
  And here, we will Start advertising BLE.
  It will start continuously transmitting BLE advertising packets and 
  will be visible to remote BLE central devices until it receives a 
  new connection.
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);

    /*
    And here, the loop function. Once everything is setup and have started advertising, 
    the device will wait for any central device. Once it is connected, it will display the 
    MAC address of the device and it will turn on the builtin LED.
    */

    while (central.connected()) {
      int Number = random(8);
      DistanceChar.writeValue(Number);
      delay(200);
    }
    /*
    Now, it will start to read analog voltage from A0, 
    which will be a value in between 0 and 1023 and will map 
    it with in the 0 to 100 range. It will print out the battery level 
    in the serial monitor and the value will be written for the batteryLevelchar charecteristics 
    and waits for 200 ms. After that the whole loop will be executed again as long as the 
    central device is connected to this peripheral device.
    */

    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());

    //Once it is disconnected, a message will be shown on the central device and LED will be turned off. 

  }

}
