import processing.serial.*;

Serial myPort;

int wdth = 400;
int hght = 300;

int transX = 40;
int transY = 30;

float prevX;
float prevY;

boolean first = true;

void setup() {
  size(500, 400);
  println(Serial.list());
  int lastport = Serial.list().length;
  String portName = Serial.list()[lastport-1]; // ultimul port 
  //serial din listă
  myPort = new Serial(this, portName, 9600); 
  myPort.bufferUntil('\n');
  background(255);
  
  rectMode(CENTER);
  scale(5);
  stroke(255, 0, 0);
  point(40, 30);
  
}
void draw() {
   if (myPort.available() > 0) {
      String xString = myPort.readStringUntil(' ');
      String yString = myPort.readStringUntil('\n');
    
      if (xString != null && yString != null) {
        float x = float(trim(xString));
        float y = float(trim(yString));
      
        float newX = x + transX;
        float newY = y + transY;
        if (first == false) {
          scale(5);
          stroke(0);
          line(prevX, prevY, newX, newY);
        }
        first = false;
        prevX = newX;
        prevY = newY;
        
        print(newX);
        print(" ");
        println(newY);
    }
  }
}
