#include<Arduino.h>
#include<Servo.h>
#include "Kheirobot_v2.h"
#include "nRF24L01_radio.h"

Kheirobot_v2* robot;
byte* rec;


void setup()
{
  robot = new Kheirobot_v2(); // instantiate the Kheirobot_v2 object
  configRX(0x06,0x3B); // configure the device as a receiver
  rec = new byte[6]; // allocate the buffer memory
  
  #ifdef __DEBUG_
  Serial.begin(9600);
  #endif
}


void loop()
{
  delay(200); // make some delay to avoid loosing the transmitted packets
  
  if(receiv(rec)) {
    // move forward and backward
    if(rec[1] == 0x1E) {// move forward
      if(robot->_state == 0) robot->first_step_forward();
      else if(robot->_state == 1 || robot->_state == 3) robot->forward_right();
      else if(robot->_state == 2) robot->forward_left();
    }
    else if(rec[1] == 0x9E) {// move backward
      if(robot->_state == 2) robot->backward_right();
      else if(robot->_state == 3 || robot->_state == 1) robot->backward_left();
    }

    // stand up on a the right leg
    if(rec[3] == 0x1E) robot->lift_front_left();
    else if(rec[3] == 0x9E) robot->lift_back_left();
    else if(rec[3] == 0x00 || rec[3] == 0x80) {
        // return to idle 
       robot->down_front_left();
       robot->down_back_left();
    }

    // stand up on a the left leg
    if(rec[2] == 0x1E) robot->lift_front_right();
    else if(rec[2]  == 0x9E) robot->lift_back_right();
    else if(rec[2] == 0x00 || rec[2] == 0x80) {
       // return to idle 
       robot->down_front_right();
       robot->down_back_right();
    }

    // shoot something with the right leg ([_])
    if(bitRead(rec[5],5) == 0) {
      if(robot->_state == 0) robot->shoot_right(); // from idle 
      else if(robot->_state == 2) robot->shoot_left_walk(); // from the walking state
      else if(robot->_state == 3 || robot->_state == 1) robot->shoot_right_walk(); // from the walking state
    }
    // shoot something with the left leg (X)
    else if(bitRead(rec[5],6) == 0) {
      if(robot->_state == 0) robot->shoot_left(); // from idle 
      else if(robot->_state == 2) robot->shoot_left_walk(); // from the walking state
      else if(robot->_state == 3 || robot->_state == 1) robot->shoot_right_walk(); // from the walking state
    }
    // splits (O)
    else if(bitRead(rec[5],7) == 0) {
      robot->split();
    }
    // return to idle (/\)
    else if(bitRead(rec[5],4) == 0)  {
      robot->idle_from_right();
      robot->idle_from_left();
    }
    // bend the robot (SELECT button)
    else if(bitRead(rec[4],0) == 0) {
      robot->bend();
    }
    // reinitialize the robot initial position (START button)
    else if(bitRead(rec[4],3) == 0) {
      robot->initialize();
    }
  }
}
