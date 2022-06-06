/*
  Controller
  Converts Arduino Micro Pro board to act as a proper controller
  Jason Wang
  June 2nd, 2022
 */

//adds the joystick library
#include <Joystick.h>

//maps out the controller as a 12 button controller with 2 joysticks
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 12);

//creating variables to map out the pins on the arduino board to match with numbers mapped on a default controller 
const int pins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16};
const int btnNr[12] = {2, 0, 7, 4, 5, 6, 8, 9, 1, 10, 11, 3}; 

void setup() {
  //sets all of the digitial pins on the Arduino board as input
  for(int i=0; i<sizeof(pins)/sizeof(pins[0]); i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
  //sets two of the analago pins as input (these will be used for the joystick)
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  //sets up the controller
  Joystick.begin();
}

void loop() {
  //sets the y and x axis of the joystick using analog pins 2 and 3 (there are 4 values available for mapping out the joysticks because the other two can be used for a seperate joystick)
  Joystick.setXAxis(map(analogRead(A3), 0, 1023, 1023, 0));
  Joystick.setYAxis(map(analogRead(A2), 0, 1023, 1023, 0));
  //detects buttons clicked through digitial pins and translates them into a controller input
  for(int i=0; i<sizeof(pins)/sizeof(pins[0]); i++) {
    if(!digitalRead(pins[i])) {
      Joystick.pressButton(btnNr[i]);
    } else {
      Joystick.releaseButton(btnNr[i]);
    }
  }
  delay(10);
}
