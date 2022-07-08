// https://github.com/innoveit/react-native-ble-manager
// https://github.com/innoveit/react-native-ble-manager
// https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
// https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String text = "";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test222"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
 if (SerialBT.available() > 0) {
    text = SerialBT.readStringUntil('\n');
    text.remove(text.length()-1, 1);
    Serial.println(text);
    if(text == "go") {
      Serial.println("Info");
    }
  }
  delay(20);
}
