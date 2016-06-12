/*
 * Pathfinder robot
 * Follows a dark line path by sensing course light level 
 * variation and adjusting direction accordingly
 */

int M1direction = 12; // polarity, HIGH or LOW
int M1speed = 3; // 0-255 analogWrite
int M1brake = 9; // start (LOW) or stop (HIGH)
// int M1currentSensor = 0;

int M2direction = 13; // polarity, HIGH or LOW
int M2speed = 11; // 0-255 analogWrite
int M2brake = 8; // start (LOW) or stop (HIGH)
// int M2currentSensor = 1;

// A0 and A1 in use by motor shield
int left = A2;   
int center = A3;
int right = A4;

int sensorValueLeft = 0;  // variable to store the value coming from the sensor

int sensorValueCenter = 0;  // variable to store the value coming from the sensor

int sensorValueRight = 0;  // variable to store the value coming from the sensor

void setup() {
    Serial.begin(9600); // serial for debugging
    
    //Setup Channel A
    pinMode(M1direction, OUTPUT); //Initiates Motor Channel A pin
    pinMode(M1brake, OUTPUT); //Initiates Brake Channel A pin
  
    // channel B
    pinMode(M2direction, OUTPUT); //Initiates Motor Channel A pin
    pinMode(M2brake, OUTPUT); //Initiates Brake Channel A pin
   
}

void loop() {
          
    // start by reading sensor values (position robot in center of path at start)
    sensorValueLeft = analogRead(left);
    sensorValueCenter = analogRead(center);
    sensorValueRight = analogRead(right);
    
    if (sensorValueCenter > sensorValueLeft && sensorValueCenter > sensorValueRight) {
      Serial.println("dead ahead");
      moveForward();
    } else if (sensorValueLeft > sensorValueCenter) {
      Serial.println("veering left");
      veerRight();
    } else if (sensorValueRight > sensorValueCenter) {
      Serial.println("veering right");
      veerLeft();
    }

    // wait before recalculation
    delay(50);
}

void moveForward() {
    //forward both motors
    digitalWrite(M1direction, LOW); //Establishes forward direction
    digitalWrite(M1brake, LOW);   //Disengage the Brake
    analogWrite(M1speed, 200);   //Spins the motor
  
    // also for motor 2
    digitalWrite(M2direction, LOW); 
    digitalWrite(M2brake, LOW);   
    analogWrite(M2speed, 200);         
}

void veerLeft() {
    digitalWrite(M1direction, LOW); //slow down motor 1
    digitalWrite(M1brake, LOW);  
    analogWrite(M1speed, 100);  
  
    digitalWrite(M2direction, LOW); //forwards motor 2
    digitalWrite(M2brake, LOW);   
    analogWrite(M2speed, 200);
}

void veerRight() {
    digitalWrite(M1direction, LOW); //forwards motor 1
    digitalWrite(M1brake, LOW);  
    analogWrite(M1speed, 200);
        
    digitalWrite(M2direction, LOW); //slow down motor 2
    digitalWrite(M2brake, LOW); 
    analogWrite(M2speed, 100);
}

void stopMotors() {
   // stop both motors
     digitalWrite(M1brake, HIGH); //Engage the Brake for Channel A
     digitalWrite(M2brake, HIGH); //Engage the Brake for Channel B
}
