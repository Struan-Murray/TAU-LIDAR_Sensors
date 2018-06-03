#include <Wire.h>
#include <VL53L0X.h>

#define NUMBER_OF_SENSORS 2


VL53L0X sensor;
VL53L0X sensor2;
VL53L0X csensor[NUMBER_OF_SENSORS];

void setup()
{
  //PWM ouputs
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  delay(500);
  Wire.begin();


  Serial.begin (9600);

  digitalWrite(4, HIGH);
  delay(150);
  Serial.println("00");
  sensor.init(true);

  Serial.println("01");
  delay(100);
  sensor.setAddress((uint8_t)22);
  Serial.println("02");

  digitalWrite(5, HIGH);
  delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)25);
  Serial.println("04");

  Serial.println("addresses set");

  sensor.setTimeout(500);
  sensor2.setTimeout(500);

  sensor.startContinuous();
  sensor2.startContinuous();

}

void loop()
{

  Serial.print("FL: ");
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  Serial.print("FR: ");
  Serial.print(sensor2.readRangeContinuousMillimeters());
  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  delay(100);
}
