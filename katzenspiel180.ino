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

const int X_INC =  20;
const int X_MIN =   0;
const int X_MAX =  90; 

const int Y_INC =   1;
const int Y_MIN =  20;
const int Y_MAX =  90;

const int X_MIN_TRGT_STEP = 40;
const int Y_MIN_TRGT_STEP = 40;

const int DELAY = 15;

int x, y;


void setup() 
{ 
  y_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  x_servo.attach(10);
  pinMode(laser, OUTPUT);
  
  Serial.begin(9600);  
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println(" Type in Box above, . ");
  Serial.println("(Decimal)(Hex)(Character)");  
  Serial.println(); 
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

void goto_pos(int x_trgt, int y_trgt) {
  x_servo.write(x_trgt);
  y_servo.write(y_trgt);
  delay(DELAY);
}

int abs_diff(int a, int b) {
  return abs(a) - abs(b);
}

int get_rand_x() {
  int rand_x = random(X_MIN, X_MAX);
  
  int diff = abs_diff(rand_x, x);
  while ( diff < X_MIN_TRGT_STEP) {
    rand_x = random(X_MIN, X_MAX);
    diff = abs_diff(rand_x, x);
  }
  Serial.println(rand_x);
  Serial.println(x);
  Serial.println();
  return rand_x;
}

int get_rand_y() {
  int rand_y = random(Y_MIN, Y_MAX);
  
  while (abs_diff(rand_y, y) < Y_MIN_TRGT_STEP) {
    rand_y = random(Y_MIN, Y_MAX);
  }
  return rand_y;
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
/*
  int i;
  for (i = 0; i < how_long; ++i) {
    int x_rnd = get_rand_x();
    int y_rnd = get_rand_y();
    goto_pos(x_rnd, y_rnd);
    delay(1000);
  }
  sweep_x_forward();
  sweep_x_backward();
*/
}

void rest(int how_long) {
  int i;
  for (i = 0; i < how_long; ++i) {
    delay(1000);
  }
}
 
void loop()
{  
  play_time(5);
  rest(10);
} 
