#include <AFMotor.h> //lirbrary for motors

int leftSensor = 25; //left
int centerSensor1 = 23; //center right
int centerSensor2 = 24; //center left
int rightSensor = 22; //right

int left_sensor_state;
int right_sensor_state;
int center_sensor_state;

int lastSensor = "right";


AF_DCMotor motorFrontL(1);
AF_DCMotor motorFrontR(2);
AF_DCMotor motorRearL(3);
AF_DCMotor motorRearR(4);

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;
boolean newControl = false; //test


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("<Arduino MEGA is ready0>");
  Serial1.println("<Arduino MEGA is ready1>");

  pinMode(22, INPUT); //right
  pinMode(23, INPUT); //center
  pinMode(24, INPUT); //center
  pinMode(25, INPUT); //left

  motorFrontL.setSpeed(200);
  motorFrontR.setSpeed(200);
  motorRearL.setSpeed(200);
  motorRearR.setSpeed(200);

  motorFrontL.run(RELEASE);
  motorFrontR.run(RELEASE);
  motorRearL.run(RELEASE);
  motorRearR.run(RELEASE);
}

void loop() {
  recvWithStartEndMarkers();
  showNewData();
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial1.available() > 0 && newData == false) {
    rc = Serial1.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
        newControl = true; //test
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("Recieved: ");
    Serial.println(receivedChars);
    newData = false;
  }
  if (strcmp(receivedChars, "StateS") == 0 && (newControl == true) ) {
    Serial1.println("State set STOP");
    motorFrontL.setSpeed(200);
    motorFrontR.setSpeed(200);
    motorRearL.setSpeed(200);
    motorRearR.setSpeed(200);
    motorFrontL.run(RELEASE);
    motorFrontR.run(RELEASE);
    motorRearL.run(RELEASE);
    motorRearR.run(RELEASE);
    newControl = false;
  }
  if (strcmp(receivedChars, "StateF") == 0 && (newControl == true) ) {
    Serial1.println("State set Forward");
    motorFrontL.setSpeed(120);
    motorFrontR.setSpeed(120);
    motorRearL.setSpeed(120);
    motorRearR.setSpeed(120);
    motorFrontL.run(FORWARD);
    motorFrontR.run(FORWARD);
    motorRearL.run(FORWARD);
    motorRearR.run(FORWARD);
    newControl = false;
  }
  if (strcmp(receivedChars, "StateR") == 0 && (newControl == true) ) {
    Serial1.println("State set Right");
    motorFrontL.setSpeed(200);
    motorFrontR.setSpeed(200);
    motorRearL.setSpeed(200);
    motorRearR.setSpeed(200);
    motorFrontL.run(FORWARD);
    motorFrontR.run(BACKWARD);
    motorRearL.run(FORWARD);
    motorRearR.run(BACKWARD);
    newControl = false;
  }
  if (strcmp(receivedChars, "StateL") == 0 && (newControl == true) ) {
    Serial1.println("State set Left");
    motorFrontL.setSpeed(200);
    motorFrontR.setSpeed(200);
    motorRearL.setSpeed(200);
    motorRearR.setSpeed(200);
    motorFrontR.run(FORWARD);
    motorFrontL.run(BACKWARD);
    motorRearR.run(FORWARD);
    motorRearL.run(BACKWARD);
    newControl = false;
  }
  if (strcmp(receivedChars, "StateB") == 0 && (newControl == true) ) {
    Serial1.println("State set Backward");
    motorFrontL.setSpeed(120);
    motorFrontR.setSpeed(120);
    motorRearL.setSpeed(120);
    motorRearR.setSpeed(120);
    motorFrontL.run(BACKWARD);
    motorFrontR.run(BACKWARD);
    motorRearL.run(BACKWARD);
    motorRearR.run(BACKWARD);
    newControl = false;
  }
}
