#include <ESP32Servo.h>

#define VRx_PIN A0   // Joystick X-axis
#define VRy_PIN A1   // Joystick Y-axis
#define SERVO_PIN D6 // Servo pin (GPIO43)

Servo myServo;

int servoAngle = 120;  // Start at center
int lastYValue = 2048;

void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(servoAngle);
}

void loop() {
  int xValue = analogRead(VRx_PIN); // Read X-axis
  int yValue = analogRead(VRy_PIN); // Read Y-axis

  // ----- Y-Axis Control: Direct angle movement -----
  if (abs(yValue - lastYValue) > 500) { // Significant up/down move
    servoAngle = map(yValue, 0, 4095, 0, 180);
    myServo.write(servoAngle);
    Serial.println("Up/Down control active");
  } else {
    // ----- X-Axis Control: Variable speed -----
    int center = 2048;
    int threshold = 400;

    if (xValue > center + threshold) { // Move Right -> Fast
      servoAngle += 8;  // Fast increment
    } else if (xValue < center - threshold) { // Move Left -> Slow
      servoAngle -= 1;  // Slow decrement
    }
    
    servoAngle = constrain(servoAngle, 0, 180);
    myServo.write(servoAngle);
  }

  Serial.print("X: "); Serial.print(xValue);
  Serial.print(" | Y: "); Serial.print(yValue);
  Serial.print(" | Servo Angle: "); Serial.println(servoAngle);

  delay(20); // Adjust responsiveness
}
