#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const uint8_t number_of_sensors = 1;

uint8_t lidar_pin[number_of_sensors];
unsigned char addresses[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};

int i = 0;



void setup() {
  int number_set_up;
  int number_unset = number_of_sensors;

  for(i = 0; i < number_of_sensors; i++)
  {
    lidar_pin[i] = 13 - i;
  }

  /*
 *lidar_pin[0] = 13;
 *lidar_pin[1] = 12;
 *lidar_pin[2] = 11;
 *lidar_pin[3] = 10;
 *lidar_pin[4] = 9;
 *lidar_pin[5] = 8;
 *lidar_pin[6] = 7;
 *lidar_pin[7] = 6;
 */
  
  Serial.begin(115200);

  while (! Serial) {
    delay(1);
  }

  for(i = 0; i < number_of_sensors; i++)
  {
    pinMode(lidar_pin[i], OUTPUT);
    digitalWrite(lidar_pin[i], LOW);
  }

  delay(10);

  for(i = 0; i < number_of_sensors; i++)
  {
    digitalWrite(lidar_pin[i], HIGH);
  }

  
  
  lox.begin(addresses[0]);
  delay(100);
  digitalWrite(lidar_pin[1], HIGH);
  lox.begin(addresses[1]);
  

  

  // wait until serial port opens for native USB devices
  
  
  /*Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); */
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.println("Distance A(mm): "); Serial.println(measure.RangeMilliMeter);
    Serial.print("Distance B(mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(1000);
}
