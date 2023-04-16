#include <Servo.h>

#define servo_pin 8
#define duration_pin 4
#define trigger_pin 2

Servo srv;
bool start = true;

struct Point {
  float x, y;
};

void setup() {
  // put your setup code here, to run once:
  pinMode(servo_pin, OUTPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(duration_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  playWithServo(servo_pin);
}

void playWithServo(int pin) {
   if (start) {
   srv.attach(servo_pin);

   for (int angle = 0; angle < 180; angle += 2) {
    srv.write(angle);
    float distance = extractDistance(angle);
    Point point = convertCoordonates(angle, distance);
    printLine(point);
    delay(1000);
    }
    
    srv.detach();
    start = false;
  }
}

int extractDistance(int angle) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  float duration = pulseIn(duration_pin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

Point convertCoordonates(float angle, float distance) {
  Point point;
  float angle_rad = angle * M_PI / 180;
  point.x = distance * cos(angle_rad);
  point.y = distance * sin(angle_rad);
  return point;
}

void printLine(Point point) {
  Serial.begin(9600);
  String coordinates = "";
  coordinates += point.x;
  coordinates += " ";
  coordinates += point.y;
  
  Serial.println(coordinates);
  delay(1000);
}
