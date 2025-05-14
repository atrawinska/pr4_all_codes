#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mySensor;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Your ESP32 I2C pins
  delay(2000);

  mySensor.setWire(&Wire);
  mySensor.beginAccel();

  mySensor.beginGyro();

  Serial.println("MPU9250 initialized");
}

void loop() {
  mySensor.accelUpdate();

  mySensor.gyroUpdate();

  Serial.println("Accel [g]: X=" + String(mySensor.accelX()) + 
                 " Y=" + String(mySensor.accelY()) + 
                 " Z=" + String(mySensor.accelZ()));

  Serial.println("Gyro [deg/s]: X=" + String(mySensor.gyroX()) + 
                 " Y=" + String(mySensor.gyroY()) + 
                 " Z=" + String(mySensor.gyroZ()));



  Serial.println("------");
  delay(1000);
}
