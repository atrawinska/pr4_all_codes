#include <MPU9250_asukiaaa.h>


MPU9250_asukiaaa mySensor;

float pitch = 0.0;
unsigned long lastTime = 0;
float alpha = 0.98; // Complementary filter weight

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // ESP32 I2C pins

  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();

  delay(2000); // Wait for sensor to stabilize

  lastTime = millis();
}

void loop() {
  mySensor.accelUpdate();
  mySensor.gyroUpdate();

  float gx = mySensor.gyroX() ;  // deg/sec
  float ay = mySensor.accelY();
  float az = mySensor.accelZ() - 1.02;

  // Time step (in seconds) 
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  //Estimate pitch from accelerometer 
  float pitchAcc = atan2(ay, az) * 180.0 / PI;

  //Integrate gyro data
  pitch = alpha * (pitch + gx * dt) + (1.0 - alpha) * pitchAcc;

  // Output pitch angle

  Serial.println(pitch);

  delay(10); // ~50 Hz update
}


