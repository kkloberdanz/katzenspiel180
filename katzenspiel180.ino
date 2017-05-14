/*
  Author : Kyle Kloberdanz
  Date   : 13 May 2017
  LICENSE: See LICENSE.txt
                     GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.
  */


#include <Servo.h>
 
//Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created
Servo x_servo;
Servo y_servo;
 
int pos = 0;    // variable to store the servo position 
int laser = 13;

const int X_INC =   1;
const int X_MIN =   0;
const int X_MAX =  90; 

const int Y_INC =   1;
const int Y_MIN =   0;
const int Y_MAX =   60;

const int X_MIN_TRGT_STEP = 40;
const int Y_MIN_TRGT_STEP = 40;

const int DELAY = 25;

int x, y;


void setup() 
{ 
  y_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  x_servo.attach(10);
  pinMode(laser, OUTPUT);
} 

void sweep_x_forward() {

  for (x = X_MIN; x < X_MAX; x += X_INC) {
    
    x_servo.write(x);
    
    for (y = Y_MIN; y < Y_MAX; y += Y_INC) {
      y_servo.write(y);
      delay(DELAY);
    }
    
    for (y = Y_MAX; y >= Y_MIN; y -= Y_INC) {
      y_servo.write(y);
      delay(DELAY);
    
    }
  }
}

void sweep_x_backward() {

  for (x = X_MAX; x >= X_MIN; x -= X_INC) {
    
    x_servo.write(x);
    
    for (y = Y_MIN; y < Y_MAX; y += Y_INC) {
      y_servo.write(y);
      delay(DELAY);
    }
    
    for (y = Y_MAX; y >= Y_MIN; y -= Y_INC) {
      y_servo.write(y);
      delay(DELAY);
    }
  }
}

// how_long: seconds to play
void play_time(int how_long) {
  int i;
  digitalWrite(laser, HIGH);
  for (i = 0; i < how_long; ++i) {
    sweep_x_forward();
    sweep_x_backward();
  }
  digitalWrite(laser, LOW);
}

void rest(long how_long) {
  int i;
  for (i = 0; i < how_long; ++i) {
    delay(1000);
  }
}
 
void loop()
{  
  play_time(2);
  delay(43200000);
} 
