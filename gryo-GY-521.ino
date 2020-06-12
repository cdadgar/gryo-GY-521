/*
 * GY-521 gyro and more
 * (based on the MPU6050)
 * datasheet (huge): https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 * 
 * features:
 * 3 axis gyro and accelerometer
 * temperature sensor
 * digital motion processor
 * 
 * 
 * use library:
 * https://github.com/adafruit/Adafruit_MPU6050
 *
 * see https://learn.adafruit.com/mpu6050-6-dof-accelerometer-and-gyro
 * VDD - 3.3 or 5 VDC
 * GND - ground
 * SCL - i2c pins (on wemos: SDA => D2, SCL => D1)
 * SDA - ic2 pins
 * XDA - auxiliary data
 * XCL - auxiliary clock
 *    the MPU6050 can collect data from other i2c sensors without cpu
 *    interaction, and use these values in calculations.
 *    (probbly beyond the scope of that we will be using it for)
 *    maybe tie this to a HMC5883L (GY-273) (i2c magnomemter (compass))?
 * ADD - i2c address
 *    low - address is 0x68 (default if pin is disconnected)
 *    high - address is 0x69
 * INT - interupt (gets set under certain conditions)
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  // start serial port
  Serial.begin(115200);
  Serial.print(F("\n\n GY-521 test\n\n"));

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  float f = temp.temperature * 9 / 5 + 32;
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" degC, ");
  Serial.print(f);
  Serial.println(" degF");

  Serial.println("");
  delay(500);
}
