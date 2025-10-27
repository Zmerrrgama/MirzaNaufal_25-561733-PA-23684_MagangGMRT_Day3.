#include <Adafruit_MPU6050.h> //initializing library
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

Servo myservo1; //initiliazing servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

#define TRIGPIR_PIN 5 //PIR Output at PIN 5
#define SERVO1_PIN 4 //Servo 1 Control at PIN 4
#define SERVO2_PIN 17 //Servo 1 Control at PIN 17
#define SERVO3_PIN 26 //Servo 1 Control at PIN 26
#define SERVO4_PIN 25 //Servo 1 Control at PIN 25
#define SERVO5_PIN 18 //Servo 1 Control at PIN 18

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!"); //checking MPU

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("MPU6050 Found!");
 
  pinMode(TRIGPIR_PIN, OUTPUT); //Attach servo pin to variable
  myservo1.attach(SERVO1_PIN);
  myservo2.attach(SERVO2_PIN);
  myservo3.attach(SERVO3_PIN);
  myservo4.attach(SERVO4_PIN);
  myservo5.attach(SERVO5_PIN);

  delay(1000);
  
}

void loop() {
  sensors_event_t a, g, t; //getting sensor value for MPU
  mpu.getEvent(&a, &g, &t);

  bool motion = digitalRead(TRIGPIR_PIN); //giving variable for PIR Sensor output
  Serial.print("\n");
  Serial.print("GERAKAN: "); //printing MPU state
  Serial.print(motion);

Serial.print("\n"); 
  //if motion being detected by PIR Sensor, this code block will get run
  if (motion==true){ //if motion is detected, each servo move into targeted angle
    myservo1.write(40);
    myservo2.write(70);
    myservo3.write(100);
    myservo4.write(130);
    myservo5.write(160);
    delay(2000);

    myservo1.write(90); //each servo return to 90 degree
    myservo2.write(90);
    myservo3.write(90);
    myservo4.write(90);
    myservo5.write(90);
    delay(2000);
  //if no motion is detected, this code block run will be run instead
  }
  else {
    // each value from left to right means the position of servo is a mapping of
    // value of gyro in x axis (in rad/s), the expected input between +4.3 to -4.3, and the expected output between 0 and 180 degree
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  int servoPos1 = map(g.gyro.x, +4.3, -4.3, 0, 180); // the (+) sign before (-) sign value indicate the servo turn counterclockwise
  myservo1.write(servoPos1);
  int servoPos2 = map(g.gyro.x, +4.3, -4.3, 0, 180);
  myservo2.write(servoPos2);

  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  int servoPos3 = map(g.gyro.y, -4.3, +4.3, 0, 180);
  myservo3.write(servoPos3);
  int servoPos4 = map(g.gyro.y, -4.3, +4.3, 0, 180);
  myservo4.write(servoPos4);

  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  int servoPos5 = map(g.gyro.z, -4.3, +4.3, 0, 180);
  myservo5.write(servoPos5); 
  // the block code below tells that if the servo not 90 degree, it will go to 90 degree after 1 second or 1000 millisecond
  if (abs(servoPos5 - 90) > 0) { 
    delay(1000);
      myservo5.write(90);
  delay(100);
}
}
delay(100);
}
